#include <QtGui>
#include "trayicon.h"

TrayIcon::TrayIcon()
    : translateKeySequence("Ctrl+C+X")
{
    setKeySequence = new QAction(tr("&Set the shortcut"));
    quit = new QAction(tr("&Quit"),this);
    connect(setKeySequence, &QAction::triggered, new KeySequenceDialog(), &QDialog::open);
    connect(quit, &QAction::triggered, qApp, &QGuiApplication::quit);

    trayIconMenu = new QMenu();
    trayIconMenu->addAction(setKeySequence);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quit);

    setContextMenu(trayIconMenu);
    setIcon(QIcon(":/icon.svg"));
}

KeySequenceDialog::KeySequenceDialog() {
    setWindowTitle("Set the shorcut");

}
