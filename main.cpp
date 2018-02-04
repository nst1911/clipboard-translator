#include <QtGui>
#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);

    QApplication::setQuitOnLastWindowClosed(false);

    Dialog dialog;
    dialog.show();

    return app.exec();
}
