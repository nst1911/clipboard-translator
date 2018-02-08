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
    void dataRequest(const QString& url); // getting data request initialization
    virtual QString getData() const;

    QNetworkReply::NetworkError getErrorFlag() const;

signals:
    void readyToRead();

private slots:
    void result(QNetworkReply*); // processing received data

private:
    QNetworkAccessManager* networkManager;
    QString data;
    QNetworkReply::NetworkError errorFlag;
};


//class TranslationDownloader : public TextFileDownloader {
//    Q_OBJECT

//public:
//    explicit TranslationDownloader(QObject *parent = nullptr);

//    void dataRequest(const QString& sourceText, const QString& language);
//    QString getData() const override;

//    QString APIkey;
//    void setAPIkey(const QString &value);
//};

#endif // TEXTFILEDOWNLOADER_H
