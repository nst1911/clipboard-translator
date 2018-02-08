#include "mainclass.h"
#include <QtGui>
#include <QJsonDocument>

MainClass::MainClass()
    : APIkey("trnsl.1.1.20180131T210131Z.fd062be4e6d5a226.f6c8a6a0a0eb3ba81b33c2e7027dab5a19e0eb9d"),
      language("en-ru")
{
    trayIcon = new TrayIcon(this);
    settingsDialog = new SettingsDialog(QKeySequence(tr("Ctrl+1")),this);
    hotkey.setShortcut(settingsDialog->getKeySequence(),true);
    downloader = new TextFileDownloader(this);

    connect(trayIcon->settings, &QAction::triggered, settingsDialog, &QDialog::open);
    connect(trayIcon->quit, &QAction::triggered, qApp, &QGuiApplication::quit);
    connect(settingsDialog, &SettingsDialog::keySequenceChanged, this, [&]() { hotkey.setShortcut(settingsDialog->getKeySequence(),true); });
    connect(&hotkey, &QHotkey::activated, this, &MainClass::translate);
}

void MainClass::setVisible(bool isVisible) {
    trayIcon->setVisible(isVisible);
}

void MainClass::translate() {
    const QClipboard *clipboard = qApp->clipboard();

    QString clipboardText(clipboard->text());

    downloader->dataRequest("https://translate.yandex.net/api/v1.5/tr.json/translate?"
                            "key=" + APIkey +
                            "&text=" + clipboardText +
                            "&lang=" + language);

    connect(downloader, &TextFileDownloader::readyToRead, this, [this,clipboardText]() {
        QJsonDocument document = QJsonDocument::fromJson(downloader->getData().toUtf8());
        QString translatedText = document.object().value("text").toArray().at(0).toString();
        trayIcon->showMessage("Окно перевода",
                    "[Исходный текст]\n" + clipboardText  +
                    "\n\n[Переведенный текст]\n" + translatedText +
                    "\n\n[Переведено сервисом «Яндекс.Переводчик» http://translate.yandex.ru/]",
                    QSystemTrayIcon::NoIcon,
                    4000);
    });
}
