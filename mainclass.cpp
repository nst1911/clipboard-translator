#include "mainclass.h"
#include <QtGui>
#include <QJsonDocument>
#include <QMetaObject>
#include <QVBoxLayout>

MainClass::MainClass()
    : APIkey("trnsl.1.1.20180131T210131Z.fd062be4e6d5a226.f6c8a6a0a0eb3ba81b33c2e7027dab5a19e0eb9d")
{
    settingsDialog = new SettingsDialog(QKeySequence("Ctrl+1"), APIkey, this);
    createAboutDialog();
    createTrayIcon();
    popUp = new PopUpWindow(4000,this);

    // Set default (Ctrl+1) hotkey for translating
    hotkey.setShortcut(settingsDialog->getCurrentKeySequence(),true);

    downloader = new TextFileDownloader(this);

    connect(settings, &QAction::triggered, settingsDialog, &QDialog::open);
    connect(about, &QAction::triggered, aboutDialog, &QDialog::open);
    connect(quit, &QAction::triggered, qApp, &QGuiApplication::quit);

    connect(settingsDialog, &SettingsDialog::keySequenceChanged, this, [this]() {
        hotkey.setShortcut(settingsDialog->getCurrentKeySequence(),true);
    });
    connect(&hotkey, &QHotkey::activated, this, &MainClass::translate);
}

void MainClass::setVisible(bool isVisible)
{
    trayIcon->setVisible(isVisible);
}

void MainClass::translate()
{
    QClipboard *clipboard = qApp->clipboard();
    QString clipboardText(clipboard->text());

    // API requires the "lang1-lang2" format, where lang1 is the source language,
    // lang2 - the translation language
    QString language = settingsDialog->getShortSourceLang() + "-" + settingsDialog->getShortTranslationLang();

    downloader->dataRequest("https://translate.yandex.net/api/v1.5/tr.json/translate?"
                            "key="   + APIkey +
                            "&text=" + clipboardText +
                            "&lang=" + language);

    connect(downloader, &TextFileDownloader::readyToRead, this, [this,clipboardText]() {
        /* Parsing the result */
        QJsonDocument document = QJsonDocument::fromJson(downloader->getData().toUtf8());
        QString translatedText = document.object().value("text").toArray().at(0).toString();

        popUp->setDuration(settingsDialog->getPopUpDuration()*1000);
        popUp->setSourceText(clipboardText, settingsDialog->getSourceLang());
        popUp->setTranslationText(translatedText, settingsDialog->getTranslationLang());
        popUp->show();
    });
}

void MainClass::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);

    settings = new QAction(tr("&Settings"),this);
    about = new QAction(tr("&About"),this);
    quit = new QAction(tr("&Quit"),this);

    trayIcon->setToolTip("Clipboard Translator\n" + tr("Press to open the context menu"));

    trayIconMenu = new QMenu();
    trayIconMenu->addAction(settings);
    trayIconMenu->addAction(about);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quit);

    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/icon.png"));
}

void MainClass::createAboutDialog() {
    aboutDialog = new QDialog(this);
    aboutDialog->setWindowTitle(tr("About"));

    QLabel* text = new QLabel(aboutDialog);
    text->setTextFormat(Qt::RichText);
    text->setTextInteractionFlags(Qt::TextBrowserInteraction);
    text->setOpenExternalLinks(true);
    text->setText(tr("<h2><div align=center>Clipboard Translator</div></h2><br>"
                     "<a href=\"https://github.com/ntrsBIG/clipboard-translator\">https://github.com/ntrsBIG/clipboard-translator</a><br><br>"
                     "<b>Clipboard Translator</b> is licensed under the <b>BSD 3-Clause License</b>.<br><br>"
                     "<b>Used open source APIs and libraries:</b> "
                        "<a href=\"https://tech.yandex.com/translate/\">Yandex.Translator API</a>, "
                        "<a href=\"https://github.com/Skycoder42/QHotkey\">QHotkey</a><br><br>"
                     "<div align=center>Copyright (c) 2018, ntrsBIG. All rights reserved.</div>"));

    QVBoxLayout* layout = new QVBoxLayout(aboutDialog);
    layout->addWidget(text);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    aboutDialog->setLayout(layout);
}
