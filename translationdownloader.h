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
    QString getTranslation() const;
    void sendText(const QString& clipboardText, const QString& resultLanguage); // getting data request initialization

signals:
    void readyToRead();

private slots:
    void result(QNetworkReply*); // processing received data

private:
    QNetworkAccessManager* networkManager;
    QString APIkey, translatedText;
};

#endif // TRANSLATIONDOWNLOADER_H
