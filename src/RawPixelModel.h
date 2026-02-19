#pragma once

#include <QAbstractTableModel>
#include <QFile>
#include <QPointer>
#include <QUrl>

class RawPixelModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(int widthPx READ widthPx WRITE setWidthPx NOTIFY specChanged)
    Q_PROPERTY(int heightPx READ heightPx WRITE setHeightPx NOTIFY specChanged)
    Q_PROPERTY(QString pixelFormat READ pixelFormat WRITE setPixelFormat NOTIFY specChanged)
    Q_PROPERTY(bool littleEndian READ littleEndian WRITE setLittleEndian NOTIFY specChanged)

    Q_PROPERTY(int bytesPerPixel READ bytesPerPixel NOTIFY specChanged)

    Q_PROPERTY(QString filePath READ filePath NOTIFY fileChanged)
    Q_PROPERTY(qint64 fileSize READ fileSize NOTIFY fileChanged)
    Q_PROPERTY(qint64 expectedSize READ expectedSize NOTIFY specChanged)
    Q_PROPERTY(bool sizeMatches READ sizeMatches NOTIFY sizeStatusChanged)

public:
    enum Roles
    {
        IsDiffRole = Qt::UserRole + 1,
        ValueRole
    };

    explicit RawPixelModel(QObject* parent = nullptr);
    ~RawPixelModel() override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    int widthPx() const { return m_width; }
    int heightPx() const { return m_height; }
    QString pixelFormat() const { return m_pixelFormat; }
    bool littleEndian() const { return m_littleEndian; }
    int bytesPerPixel() const;

    QString filePath() const { return m_filePath; }
    qint64 fileSize() const { return m_fileSize; }
    qint64 expectedSize() const;
    bool sizeMatches() const;

    void setWidthPx(int v);
    void setHeightPx(int v);
    void setPixelFormat(const QString& v);
    void setLittleEndian(bool v);

    Q_INVOKABLE bool loadFile(const QUrl& url);
    Q_INVOKABLE QVariantMap inferSpecFromFileName(const QUrl& url);
    Q_INVOKABLE QVariantMap inferSpecFromFilePath(const QString& path);
    Q_INVOKABLE void setCompareTo(QObject* otherModel);

signals:
    void specChanged();
    void fileChanged();
    void sizeStatusChanged();

private:
    void resetModel();
    void closeMapped();
    bool mapFile(const QString& path);

    bool isComparableToOther() const;
    bool cellDiffers(int r, int c) const;

    inline quint8 byteAt(qint64 off) const;

private:
    int m_width = 0;
    int m_height = 0;
    QString m_pixelFormat = "Mono8";
    bool m_littleEndian = true;

    QString m_filePath;
    qint64 m_fileSize = 0;

    QFile m_file;
    uchar* m_map = nullptr;
    qint64 m_mapSize = 0;

    QPointer<RawPixelModel> m_other;
};
