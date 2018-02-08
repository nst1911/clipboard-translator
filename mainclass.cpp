#include "mainclass.h"
#include <QtGui>

MainClass::MainClass()
{
    trayIcon = new TrayIcon(this);
    settingsDialog = new SettingsDialog(QKeySequence(tr("Ctrl+1")),this);
    hotkey.setShortcut(settingsDialog->getKeySequence(),true);
    downloader = new TranslationDownloader(this);

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

    downloader->sendText(clipboardText,"ru");

    connect(downloader, &TranslationDownloader::readyToRead, this, [this,clipboardText]() {
        trayIcon->showMessage("Окно перевода",
                    "[Исходный текст]\n" + clipboardText  +
                    "\n\n[Переведенный текст]\n" + downloader->getTranslation() +
                    "\n\n[Переведено сервисом «Яндекс.Переводчик» http://translate.yandex.ru/]",
                    QSystemTrayIcon::NoIcon,
                    4000);
    });
}
