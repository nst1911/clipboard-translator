#include <QtGui>
#include <QApplication>
#include "mainclass.h"
#include <QComboBox>

#include "textfiledownloader.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);

    QApplication::setQuitOnLastWindowClosed(false);

    MainClass mainClass;
    mainClass.show();

    return app.exec();
}
