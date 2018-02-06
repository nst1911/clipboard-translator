#include "mainclass.h"
#include <QtGui>

MainClass::MainClass()
{
    trayIcon = new TrayIcon(this);
    setDialog = new KeySequenceDialog(QKeySequence(tr("Ctrl+1")));
    hotkey.setShortcut(setDialog->getKeySequence(),true);
    downloader = new TranslationDownloader(this);

    connect(trayIcon->setKeySequence, &QAction::triggered, setDialog, &QDialog::open);
    connect(trayIcon->quit, &QAction::triggered, qApp, &QGuiApplication::quit);
    connect(&hotkey, &QHotkey::activated, this, &MainClass::translate);
    connect(setDialog, &KeySequenceDialog::keySequenceChanged, this, [&]() { hotkey.setShortcut(setDialog->getKeySequence(),true); });
}

void MainClass::setVisible(bool isVisible) {
    trayIcon->setVisible(isVisible);
}

void MainClass::translate() {
    const QClipboard *clipboard = qApp->clipboard();

    QString clipboardText(clipboard->text());

    downloader->sendText(clipboardText);

    connect(downloader, &TranslationDownloader::readyToRead, this, [this,clipboardText]() {
        trayIcon->showMessage("Окно перевода",
                    "[Исходный текст]\n" + clipboardText  +
                    "\n\n[Переведенный текст]\n" + downloader->getTranslation() +
                    "\n\n[Переведено сервисом «Яндекс.Переводчик» http://translate.yandex.ru/]",
                    QSystemTrayIcon::NoIcon,
                    4000);
    });
}
