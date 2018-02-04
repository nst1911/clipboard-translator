#include <QtGui>
#include "dialog.h"

#include <QAction>

Dialog::Dialog()
{
    createActions();
    createTrayIcon();
    trayIcon->show();
}

void Dialog::createActions()
{
    minimize = new QAction(tr("&Minimize"),this);
    restore = new QAction(tr("&Restore"),this);
    quit = new QAction(tr("&Quit"),this);

    connect(minimize, &QAction::triggered, this, &Dialog::hide);
    connect(restore, &QAction::triggered, this, &Dialog::showNormal);
    connect(quit, &QAction::triggered, qApp, &QGuiApplication::quit);
}

void Dialog::createTrayIcon() {
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimize);
    trayIconMenu->addAction(restore);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quit);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/icon.svg"));
}

void Dialog::setVisible(bool visible)
{
    minimize->setEnabled(visible);
    restore->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}
