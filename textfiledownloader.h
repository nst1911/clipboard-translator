#ifndef TEXTFILEDOWNLOADER_H
#define TEXTFILEDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class TextFileDownloader : public QObject
{
   Q_OBJECT

public:
    explicit TextFileDownloader(QObject *parent = nullptr);

    void dataRequest(const QString& url);
    inline QString getData() const { return data; }

signals:
    void readyToRead();

private:
    QNetworkAccessManager* networkManager;
    QString data;
};

#endif // TEXTFILEDOWNLOADER_H
