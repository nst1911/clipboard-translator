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

    void    dataRequest(const QString& url); // getting data request initialization
    QString getData() const;

signals:
    void readyToRead();

private slots:
    void result(QNetworkReply*); // processing received data

private:
    QNetworkAccessManager* networkManager;
    QString data;
};

#endif // TEXTFILEDOWNLOADER_H
