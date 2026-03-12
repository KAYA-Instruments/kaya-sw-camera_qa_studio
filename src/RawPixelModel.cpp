#include "RawPixelModel.h"

#include <QFileInfo>
#include <QRegularExpression>
#include <QDir>
#include <cstring>

static QString normalizePixelFormat(const QString& s);

static QVariantMap inferFromTomlFile(const QString& tomlPath)
{
    QVariantMap out;

    QFile f(tomlPath);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        out["ok"] = false;
        return out;
    }

    const QString txt = QString::fromUtf8(f.readAll());

    // Minimal TOML parsing for this viewer: only Width, Height, PixelFormat
    const QRegularExpression reW(R"((?:^|\n)\s*Width\s*=\s*(\d+)\s*(?:\n|$))",
                                 QRegularExpression::MultilineOption);
    const QRegularExpression reH(R"((?:^|\n)\s*Height\s*=\s*(\d+)\s*(?:\n|$))",
                                 QRegularExpression::MultilineOption);
    const QRegularExpression reP(
        R"toml((?:^|\n)\s*PixelFormat\s*=\s*"?([A-Za-z0-9_]+)"?\s*(?:\n|$))toml",
        QRegularExpression::MultilineOption);

    bool any = false;

    const auto mW = reW.match(txt);
    if (mW.hasMatch())
    {
        out["width"] = mW.captured(1).toInt();
        any = true;
    }

    const auto mH = reH.match(txt);
    if (mH.hasMatch())
    {
        out["height"] = mH.captured(1).toInt();
        any = true;
    }

    const auto mP = reP.match(txt);
    if (mP.hasMatch())
    {
        out["pixelFormat"] = normalizePixelFormat(mP.captured(1));
        any = true;
    }

    out["ok"] = any;
    return out;
}

static QString normalizePixelFormat(const QString& s)
{
    const QString t = s.trimmed();
    if (t.isEmpty()) return "Mono8";

    // Accept Bayer{RG,GR,GB,BG}{8,10,12,14,16} and normalize to Mono{bits}.
    static const QRegularExpression reBayer(
        R"(^Bayer(?:RG|GR|GB|BG)(8|10|12|14|16)$)",
        QRegularExpression::CaseInsensitiveOption);
    const auto mb = reBayer.match(t);
    if (mb.hasMatch())
    {
        return "Mono" + mb.captured(1);
    }

    return t;
}

static QVariantMap inferFromNameToMap(const QString& fileName, const QString& rawDirPath)
{
    QVariantMap out;
    bool any = false;

    static const QRegularExpression reArg(
        R"arg((?<refcfg>--refconfig\s+(?:"(?<ref_dq>[^"]+\.toml)"|'(?<ref_sq>[^']+\.toml)'|(?<ref_plain>[^\s]+\.toml)))|(?<width>--Width\s+(?<width_val>\d+))|(?<height>--Height\s+(?<height_val>\d+))|(?<pixfmt>--PixelFormat\s+(?<pixfmt_val>[A-Za-z0-9_]+)))arg",
        QRegularExpression::CaseInsensitiveOption);

    auto it = reArg.globalMatch(fileName);
    while (it.hasNext())
    {
        const auto m = it.next();

        if (!m.captured("refcfg").isEmpty())
        {
            QString ref = m.captured("ref_dq");
            if (ref.isEmpty()) ref = m.captured("ref_sq");
            if (ref.isEmpty()) ref = m.captured("ref_plain");

            if (!ref.isEmpty())
            {
                const QString tomlPath = QDir(rawDirPath).filePath(ref);
                const QVariantMap t = inferFromTomlFile(tomlPath);
                if (t.value("ok").toBool())
                {
                    if (t.contains("width")) out["width"] = t.value("width");
                    if (t.contains("height")) out["height"] = t.value("height");
                    if (t.contains("pixelFormat")) out["pixelFormat"] = t.value("pixelFormat");
                    any = true;
                }
            }
        }
        else if (!m.captured("width").isEmpty())
        {
            out["width"] = m.captured("width_val").toInt();
            any = true;
        }
        else if (!m.captured("height").isEmpty())
        {
            out["height"] = m.captured("height_val").toInt();
            any = true;
        }
        else if (!m.captured("pixfmt").isEmpty())
        {
            out["pixelFormat"] = normalizePixelFormat(m.captured("pixfmt_val"));
            any = true;
        }
    }

    out["ok"] = any;
    return out;
}

RawPixelModel::RawPixelModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

RawPixelModel::~RawPixelModel()
{
    closeMapped();
}

int RawPixelModel::bytesPerPixel() const
{
    const QString pf = m_pixelFormat.trimmed();

    // Mono{8,10,12,14,16}
    if (pf.compare("Mono8", Qt::CaseInsensitive) == 0) return 1;
    if (pf.compare("Mono10", Qt::CaseInsensitive) == 0) return 2;
    if (pf.compare("Mono12", Qt::CaseInsensitive) == 0) return 2;
    if (pf.compare("Mono14", Qt::CaseInsensitive) == 0) return 2;
    if (pf.compare("Mono16", Qt::CaseInsensitive) == 0) return 2;

    // Bayer{RG,GR,GB,BG}{8,10,12,14,16} (same storage as Mono for this viewer)
    static const QRegularExpression reBayer(
        R"(^Bayer(?:RG|GR|GB|BG)(8|10|12|14|16)$)",
        QRegularExpression::CaseInsensitiveOption);
    const auto mb = reBayer.match(pf);
    if (mb.hasMatch())
    {
        const int bits = mb.captured(1).toInt();
        return (bits <= 8) ? 1 : 2;
    }

    return 1;
}

qint64 RawPixelModel::expectedSize() const
{
    if (m_width <= 0 || m_height <= 0) return 0;
    return qint64(m_width) * qint64(m_height) * qint64(bytesPerPixel());
}

bool RawPixelModel::sizeMatches() const
{
    const qint64 exp = expectedSize();
    if (exp <= 0) return false;
    return (m_fileSize == exp);
}

int RawPixelModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;
    return (m_height > 0) ? m_height : 0;
}

int RawPixelModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;
    return (m_width > 0) ? m_width : 0;
}

QVariant RawPixelModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return {};

    const int r = index.row();
    const int c = index.column();
    if (r < 0 || c < 0 || r >= m_height || c >= m_width) return {};

    if (!m_map || m_mapSize <= 0) return {};

    const int bpp = bytesPerPixel();
    const qint64 off = (qint64(r) * qint64(m_width) + qint64(c)) * qint64(bpp);
    if (off < 0 || off + bpp > m_mapSize) return {};

    if (role == Qt::DisplayRole)
    {
        if (bpp == 1)
        {
            const quint8 v = byteAt(off);
            return QString("%1").arg(v, 2, 16, QChar('0')).toUpper();
        }
        else
        {
            quint8 b0 = byteAt(off);
            quint8 b1 = byteAt(off + 1);
            if (!m_littleEndian) std::swap(b0, b1);
            return QString("%1 %2")
                .arg(b0, 2, 16, QChar('0')).toUpper()
                .arg(b1, 2, 16, QChar('0')).toUpper();
        }
    }

    if (role == IsDiffRole)
    {
        return cellDiffers(r, c);
    }

    if (role == ValueRole)
    {
        if (bpp == 1) return int(byteAt(off));

        quint16 v = 0;
        const quint8 b0 = byteAt(off);
        const quint8 b1 = byteAt(off + 1);
        if (m_littleEndian) v = quint16(b0) | (quint16(b1) << 8);
        else v = quint16(b1) | (quint16(b0) << 8);
        return int(v);
    }

    return {};
}

QHash<int, QByteArray> RawPixelModel::roleNames() const
{
    auto r = QAbstractTableModel::roleNames();
    r[IsDiffRole] = "isDiff";
    r[ValueRole] = "value";
    return r;
}

void RawPixelModel::setWidthPx(int v)
{
    if (v == m_width) return;
    m_width = v;
    resetModel();
    emit specChanged();
    emit sizeStatusChanged();
}

void RawPixelModel::setHeightPx(int v)
{
    if (v == m_height) return;
    m_height = v;
    resetModel();
    emit specChanged();
    emit sizeStatusChanged();
}

void RawPixelModel::setPixelFormat(const QString& v)
{
    const QString nv = normalizePixelFormat(v);
    if (nv == m_pixelFormat) return;
    m_pixelFormat = nv;
    resetModel();
    emit specChanged();
    emit sizeStatusChanged();
}

void RawPixelModel::setLittleEndian(bool v)
{
    if (v == m_littleEndian) return;
    m_littleEndian = v;
    emit specChanged();
    if (m_width > 0 && m_height > 0)
    {
        emit dataChanged(index(0,0), index(m_height-1, m_width-1), {Qt::DisplayRole, ValueRole});
    }
}

void RawPixelModel::resetModel()
{
    beginResetModel();
    endResetModel();

    refreshDiff();
    if (m_other) m_other->refreshDiff();
}

void RawPixelModel::refreshDiff()
{
    if (m_width <= 0 || m_height <= 0) return;

    // Emit "all roles changed" to force QML TableView to refresh delegate bindings
    emit dataChanged(index(0, 0), index(m_height - 1, m_width - 1));
}


void RawPixelModel::closeMapped()
{
    if (m_map)
    {
        m_file.unmap(m_map);
        m_map = nullptr;
        m_mapSize = 0;
    }
    if (m_file.isOpen())
    {
        m_file.close();
    }
}

bool RawPixelModel::mapFile(const QString& path)
{
    closeMapped();

    m_file.setFileName(path);
    if (!m_file.open(QIODevice::ReadOnly)) return false;

    m_fileSize = m_file.size();
    if (m_fileSize <= 0)
    {
        m_file.close();
        return false;
    }

    m_map = m_file.map(0, m_fileSize);
    if (!m_map)
    {
        m_file.close();
        return false;
    }

    m_mapSize = m_fileSize;
    return true;
}

bool RawPixelModel::loadFile(const QUrl& url)
{
    const QString path = url.isLocalFile() ? url.toLocalFile() : url.toString();
    if (path.isEmpty()) return false;

    const QFileInfo fi(path);

    beginResetModel();
    const bool ok = mapFile(path);
    m_filePath = fi.absoluteFilePath();
    endResetModel();

    emit fileChanged();
    emit sizeStatusChanged();

    refreshDiff();
    if (m_other) m_other->refreshDiff();


    return ok;
}

QVariantMap RawPixelModel::inferSpecFromFileName(const QUrl& url)
{
    const QString path = url.isLocalFile() ? url.toLocalFile() : url.toString();
    const QFileInfo fi(path);

    const QVariantMap inferred = inferFromNameToMap(fi.fileName(), fi.absolutePath());

    if (inferred.value("ok").toBool())
    {
        if (inferred.contains("width")) setWidthPx(inferred.value("width").toInt());
        if (inferred.contains("height")) setHeightPx(inferred.value("height").toInt());
        if (inferred.contains("pixelFormat")) setPixelFormat(inferred.value("pixelFormat").toString());
    }

    return inferred;
}

QVariantMap RawPixelModel::inferSpecFromFilePath(const QString& path)
{
    const QFileInfo fi(path);

    const QVariantMap inferred = inferFromNameToMap(fi.fileName(), fi.absolutePath());

    if (inferred.value("ok").toBool())
    {
        if (inferred.contains("width")) setWidthPx(inferred.value("width").toInt());
        if (inferred.contains("height")) setHeightPx(inferred.value("height").toInt());
        if (inferred.contains("pixelFormat")) setPixelFormat(inferred.value("pixelFormat").toString());
    }

    return inferred;
}

void RawPixelModel::setCompareTo(QObject* otherModel)
{
    auto* om = qobject_cast<RawPixelModel*>(otherModel);
    if (om == m_other) return;

    m_other = om;

    refreshDiff();
    if (m_other) m_other->refreshDiff();
}

QVariantMap RawPixelModel::findFirstDiff() const
{
    QVariantMap out;

    if (!isComparableToOther())
    {
        out["ok"] = false;
        out["row"] = -1;
        out["col"] = -1;
        return out;
    }

    for (int r = 0; r < m_height; ++r)
    {
        for (int c = 0; c < m_width; ++c)
        {
            if (cellDiffers(r, c))
            {
                out["ok"] = true;
                out["row"] = r;
                out["col"] = c;
                return out;
            }
        }
    }

    out["ok"] = false;
    out["row"] = -1;
    out["col"] = -1;
    return out;
}


bool RawPixelModel::isComparableToOther() const
{
    if (!m_other) return false;
    if (!m_map || !m_other->m_map) return false;
    if (m_width <= 0 || m_height <= 0) return false;

    if (m_width != m_other->m_width) return false;
    if (m_height != m_other->m_height) return false;
    if (bytesPerPixel() != m_other->bytesPerPixel()) return false;
    return true;
}

bool RawPixelModel::cellDiffers(int r, int c) const
{
    if (!isComparableToOther()) return false;

    const int bpp = bytesPerPixel();
    const qint64 off = (qint64(r) * qint64(m_width) + qint64(c)) * qint64(bpp);
    if (off < 0 || off + bpp > m_mapSize) return false;
    if (off + bpp > m_other->m_mapSize) return false;

    for (int i = 0; i < bpp; ++i)
    {
        if (m_map[off + i] != m_other->m_map[off + i]) return true;
    }
    return false;
}

int RawPixelModel::nextDiffRow(int afterRow) const
{
    if (!isComparableToOther()) return -1;

    int start = afterRow + 1;
    if (start < 0) start = 0;

    const int bpp = bytesPerPixel();
    const qint64 rowBytes = qint64(m_width) * qint64(bpp);

    for (int r = start; r < m_height; ++r)
    {
        const qint64 off = qint64(r) * rowBytes;
        if (off < 0 || off + rowBytes > m_mapSize) return -1;
        if (off + rowBytes > m_other->m_mapSize) return -1;

        if (std::memcmp(m_map + off, m_other->m_map + off, size_t(rowBytes)) != 0)
        {
            return r;
        }
    }

    return -1;
}

int RawPixelModel::prevDiffRow(int beforeRow) const
{
    if (!isComparableToOther()) return -1;

    int start = beforeRow - 1;
    if (start >= m_height) start = m_height - 1;

    const int bpp = bytesPerPixel();
    const qint64 rowBytes = qint64(m_width) * qint64(bpp);

    for (int r = start; r >= 0; --r)
    {
        const qint64 off = qint64(r) * rowBytes;
        if (off < 0 || off + rowBytes > m_mapSize) return -1;
        if (off + rowBytes > m_other->m_mapSize) return -1;

        if (std::memcmp(m_map + off, m_other->m_map + off, size_t(rowBytes)) != 0)
        {
            return r;
        }
    }

    return -1;
}

int RawPixelModel::firstDiffColInRow(int row) const
{
    if (!isComparableToOther()) return -1;
    if (row < 0 || row >= m_height) return -1;

    const int bpp = bytesPerPixel();
    const qint64 rowOff = qint64(row) * qint64(m_width) * qint64(bpp);

    for (int c = 0; c < m_width; ++c)
    {
        const qint64 off = rowOff + qint64(c) * qint64(bpp);
        if (off < 0 || off + bpp > m_mapSize) return -1;
        if (off + bpp > m_other->m_mapSize) return -1;

        if (std::memcmp(m_map + off, m_other->m_map + off, size_t(bpp)) != 0)
        {
            return c;
        }
    }

    return -1;
}

int RawPixelModel::nextDiffColInRow(int row, int afterCol) const
{
    if (!isComparableToOther()) return -1;
    if (row < 0 || row >= m_height) return -1;

    int start = afterCol + 1;
    if (start < 0) start = 0;

    const int bpp = bytesPerPixel();
    const qint64 rowOff = qint64(row) * qint64(m_width) * qint64(bpp);

    for (int c = start; c < m_width; ++c)
    {
        const qint64 off = rowOff + qint64(c) * qint64(bpp);
        if (off < 0 || off + bpp > m_mapSize) return -1;
        if (off + bpp > m_other->m_mapSize) return -1;

        if (std::memcmp(m_map + off, m_other->m_map + off, size_t(bpp)) != 0)
        {
            return c;
        }
    }

    return -1;
}

int RawPixelModel::prevDiffColInRow(int row, int beforeCol) const
{
    if (!isComparableToOther()) return -1;
    if (row < 0 || row >= m_height) return -1;

    int start = beforeCol - 1;
    if (start >= m_width) start = m_width - 1;

    const int bpp = bytesPerPixel();
    const qint64 rowOff = qint64(row) * qint64(m_width) * qint64(bpp);

    for (int c = start; c >= 0; --c)
    {
        const qint64 off = rowOff + qint64(c) * qint64(bpp);
        if (off < 0 || off + bpp > m_mapSize) return -1;
        if (off + bpp > m_other->m_mapSize) return -1;

        if (std::memcmp(m_map + off, m_other->m_map + off, size_t(bpp)) != 0)
        {
            return c;
        }
    }

    return -1;
}


quint8 RawPixelModel::byteAt(qint64 off) const
{
    return quint8(m_map[off]);
}
