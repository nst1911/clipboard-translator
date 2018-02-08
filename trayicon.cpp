#include <QtGui>
#include "trayicon.h"

TrayIcon::TrayIcon(QObject* parent)
    : QSystemTrayIcon(parent)
{
    settings = new QAction(tr("&Settings"),this);
    quit = new QAction(tr("&Quit"),this);

    setToolTip("Clipboard Translator\n" + tr("Press to open the context menu"));

    trayIconMenu = new QMenu();
    trayIconMenu->addAction(settings);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quit);

    setContextMenu(trayIconMenu);
    setIcon(QIcon(":/icon.png"));
}


