#include <QtGui>
#include <QApplication>
#include "trayicon.h"
#include "translationdownloader.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);

    QApplication::setQuitOnLastWindowClosed(false);

    TrayIcon trayIcon;
    trayIcon.show();

    return app.exec();
}
