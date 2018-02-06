#ifndef TRANSLATIONDOWNLOADER_H
#define TRANSLATIONDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class TranslationDownloader : public QObject
{
    Q_OBJECT
public:
    explicit TranslationDownloader(QObject *parent = nullptr);

signals:
    void readyToRead();

public:
    QString getTranslation() const;
    void sendText(const QString& clipboardText); // getting data request initialization

private slots:
    void result(QNetworkReply*); // processing received data

private:
    QNetworkAccessManager* networkManager;

    QString APIkey, translate;


    QNetworkReply::NetworkError errorFlag;



};

#endif // TRANSLATIONDOWNLOADER_H
