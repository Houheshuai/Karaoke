#ifndef MYNETWORK_H
#define MYNETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <Qimage>
#include <QPixmap>

//网络有关，下载歌曲唱片、歌词
class MyNetWork : public QObject
{
    Q_OBJECT

public:
    explicit MyNetWork(QObject *parent = 0);
    ~MyNetWork();
    const QImage &BgWhiteChange(QImage& image , int brightness);
signals:
    void sig_reqMvfinished(const QString&);
    void sig_reqSongFinished(const QByteArray&);
    void sig_reqSongNextPagefinished(const QByteArray&);

    void dolrcworkfinished(const QByteArray&,const QString&);
    void setpic(const QByteArray&,const QString&);
    void sig_setBgpix(const QVector<QPixmap>&,const QString& author);
public slots:
    void reqMv(const QString&);
    void reqAlbum(const QString &name,const QString &savelocal);
    void reqSong(const QString&);
    void reqSongNextPage();
    void reqLrc(const QString &,qint64 totaltime,const QString &saveloaction);
    void reqBgPic(const QString &author);
private:

    int m_pageindex;
    QString m_songName;
};

#endif // MYNETWORK_H
