#include "textfiledownloader.h"
#include <QNetworkRequest>
#include <QFile>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

TextFileDownloader::TextFileDownloader(QObject *parent)
    : QObject(parent), errorFlag(QNetworkReply::NetworkError::NoError)
{
    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &TextFileDownloader::result);
}

void TextFileDownloader::dataRequest(const QString& url)
{
    QUrl qurl(url);
    QNetworkRequest request(qurl);
    networkManager->get(request);
}

void TextFileDownloader::result(QNetworkReply* reply) {
    data = (reply->error()) ? reply->errorString() : reply->readAll();
    emit readyToRead();
}

QNetworkReply::NetworkError TextFileDownloader::getErrorFlag() const
{
    return errorFlag;
}

QString TextFileDownloader::getData() const { return data; }


/*


TranslationDownloader::TranslationDownloader(QObject *parent)
    : TextFileDownloader(parent),
      APIkey("trnsl.1.1.20180131T210131Z.fd062be4e6d5a226.f6c8a6a0a0eb3ba81b33c2e7027dab5a19e0eb9d")
{
}

void TranslationDownloader::setAPIkey(const QString &value)
{
    APIkey = value;
}

void TranslationDownloader::dataRequest(const QString& sourceText, const QString& language)
{
    TextFileDownloader::dataRequest("https://translate.yandex.net/api/v1.5/tr.json/translate?"
                                    "key=" + APIkey +
                                    "&text=" + sourceText +
                                    "&lang=" + language);
}

QString TranslationDownloader::getData() const
{
    if (getErrorFlag())
        return TextFileDownloader::getData();
    else {
        QJsonDocument document = QJsonDocument::fromJson(TextFileDownloader::getData().toUtf8());
        return document.object().value("text").toArray().at(0).toString();
    }
}*/
