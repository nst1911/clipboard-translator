#include "translationdownloader.h"
#include <QNetworkRequest>
#include <QTextCodec>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

TranslationDownloader::TranslationDownloader(QObject *parent)
    : QObject(parent),
      APIkey("trnsl.1.1.20180131T210131Z.fd062be4e6d5a226.f6c8a6a0a0eb3ba81b33c2e7027dab5a19e0eb9d")
{
    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &TranslationDownloader::result);
}

void TranslationDownloader::sendText(const QString& clipboardText, const QString& resultLanguage)
{
    QUrl url("https://translate.yandex.net/api/v1.5/tr.json/translate?"
             "key=" + APIkey +
             "&text=" + clipboardText +
             "&lang=" + resultLanguage);
    QNetworkRequest request(url);
    networkManager->get(request);
}

void TranslationDownloader::result(QNetworkReply* reply) {
    if (reply->error()) {
        translatedText = reply->errorString();
        qDebug() << reply->errorString();
    }
    else {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        translatedText = document.object().value("text").toArray().at(0).toString();
    }
    emit readyToRead();
}

QString TranslationDownloader::getTranslation() const
{
       return translatedText;
}
