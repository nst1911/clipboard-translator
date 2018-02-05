#include <QtGui>
#include "dialog.h"

Dialog::Dialog()
    : translateKeySequence("Ctrl+C+X")
{
    setVisible(false);
    createActions();
    createTrayIcon();
    trayIcon->show();
}

void Dialog::createActions()
{
    setKeySequence = new QAction(tr("&Set the shortcut"));
    quit = new QAction(tr("&Quit"),this);
    connect(setKeySequence, &QAction::triggered, new KeySequenceDialog(), &Dialog::open);
    connect(quit, &QAction::triggered, qApp, &QGuiApplication::quit);
}

void Dialog::createTrayIcon() {
    trayIconMenu = new QMenu(this);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(setKeySequence);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quit);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/icon.svg"));
}

KeySequenceDialog::KeySequenceDialog() {
    setWindowTitle("Set the shorcut");

}
