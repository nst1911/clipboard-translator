#include <QtGui>
#include <QApplication>
#include "mainclass.h"

#include "popupwindow.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);

    QApplication::setQuitOnLastWindowClosed(false);

    MainClass mainClass;
    mainClass.show();

//    PopUpWindow* p = new PopUpWindow();
//    p->setTranslationText("text","Russian");
//    p->setSourceText("text","English");
//    p->show();

    return app.exec();
}
