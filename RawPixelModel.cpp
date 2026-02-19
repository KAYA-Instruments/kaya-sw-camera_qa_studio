#include "RawPixelModel.h"

#include <QFileInfo>
#include <QRegularExpression>

static QString normalizePixelFormat(const QString& s)
{
    const QString t = s.trimmed();
    if (t.isEmpty()) return "Mono8";
    return t;
}

static QVariantMap inferFromNameToMap(const QString& fileName)
{
    QVariantMap out;

    const QRegularExpression reW(R"(--Width\s+(\d+))");
    const QRegularExpression reH(R"(--Height\s+(\d+))");
    const QRegularExpression reP(R"(--PixelFormat\s+([A-Za-z0-9_]+))");

    const auto mW = reW.match(fileName);
    const auto mH = reH.match(fileName);
    const auto mP = reP.match(fileName);

    bool any = false;

    if (mW.hasMatch())
    {
        out["width"] = mW.captured(1).toInt();
        any = true;
    }
    if (mH.hasMatch())
    {
        out["height"] = mH.captured(1).toInt();
        any = true;
    }
    if (mP.hasMatch())
    {
        out["pixelFormat"] = mP.captured(1);
        any = true;
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
    if (pf.compare("Mono8", Qt::CaseInsensitive) == 0) return 1;

    // Minimal viewer: treat Mono10/Mono12/Mono16 as stored in 16-bit (2 bytes/pixel)
    if (pf.compare("Mono10", Qt::CaseInsensitive) == 0) return 2;
    if (pf.compare("Mono12", Qt::CaseInsensitive) == 0) return 2;
    if (pf.compare("Mono16", Qt::CaseInsensitive) == 0) return 2;

    // Default fallback
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

    if (m_other)
    {
        emit dataChanged(index(0,0), index(qMax(0,m_height-1), qMax(0,m_width-1)), {IsDiffRole});
    }
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

    if (m_other)
    {
        emit dataChanged(index(0,0), index(qMax(0,m_height-1), qMax(0,m_width-1)), {IsDiffRole});
    }

    return ok;
}

QVariantMap RawPixelModel::inferSpecFromFileName(const QUrl& url)
{
    const QString path = url.isLocalFile() ? url.toLocalFile() : url.toString();
    const QFileInfo fi(path);
    const QVariantMap inferred = inferFromNameToMap(fi.fileName());

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
    const QVariantMap inferred = inferFromNameToMap(fi.fileName());

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

    if (m_height > 0 && m_width > 0)
    {
        emit dataChanged(index(0,0), index(m_height-1, m_width-1), {IsDiffRole});
    }
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

quint8 RawPixelModel::byteAt(qint64 off) const
{
    return quint8(m_map[off]);
}
