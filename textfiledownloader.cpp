#include "textfiledownloader.h"
#include <QNetworkRequest>
#include <QFile>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

TextFileDownloader::TextFileDownloader(QObject *parent)
    : QObject(parent)
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

QString TextFileDownloader::getData() const { return data; }
