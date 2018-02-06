#include <QtGui>
#include "trayicon.h"

TrayIcon::TrayIcon(QObject* parent)
    : QSystemTrayIcon(parent)
{
    setKeySequence = new QAction(tr("&Set the shortcut"),this);
    quit = new QAction(tr("&Quit"),this);

    trayIconMenu = new QMenu();
    trayIconMenu->addAction(setKeySequence);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quit);

    setContextMenu(trayIconMenu);
    setIcon(QIcon(":/icon.png"));
}


