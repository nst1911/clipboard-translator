#include <QtGui>
#include "trayicon.h"

TrayIcon::TrayIcon()
{
    setKeySequence = new QAction(tr("&Set the shortcut"));
    quit = new QAction(tr("&Quit"),this);
    setDialog = new KeySequenceDialog(QKeySequence(tr("Alt+1")));

    connect(setKeySequence, &QAction::triggered, setDialog, &QDialog::open);
    connect(quit, &QAction::triggered, qApp, &QGuiApplication::quit);

    trayIconMenu = new QMenu();
    trayIconMenu->addAction(setKeySequence);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quit);

    setContextMenu(trayIconMenu);
    setIcon(QIcon(":/icon.svg"));
}

KeySequenceDialog::KeySequenceDialog(QKeySequence keySequence)
    : translateKeySequence(keySequence)
{
    labelBeforeField = new QLabel(tr("Current shortcut: "), this);

    keySequenceField = new QLineEdit(translateKeySequence.toString(), this);
    keySequenceField->setReadOnly(true);

    setButton = new QPushButton(tr("Enter new shortcut"),this);

    labelAfterButton = new QLabel(tr("Press any combination of keys (Ctrl+Shift+D, Alt+5, ...)\n"
                          "Several combinations may not work on your operation system."));
    labelAfterButton->setVisible(false);

    connect(setButton,&QPushButton::clicked,this,[&](){ isClicked = true; labelAfterButton->setVisible(true); });

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(labelBeforeField,0,0);
    layout->addWidget(keySequenceField,0,1);
    layout->addWidget(setButton,1,1);
    layout->addWidget(labelAfterButton,2,0,1,2);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

    setWindowTitle("Set the translate shortcut");
}

void KeySequenceDialog::keyPressEvent(QKeyEvent* keyEvent) {
    if (isClicked) {
        int keyInt = keyEvent->key();

        if (keyInt == Qt::Key_unknown) return;

        // Only single click of modifier
        if (keyInt == Qt::Key_Control || keyInt == Qt::Key_Shift   ||
            keyInt == Qt::Key_Alt     || keyInt == Qt::Key_Meta)
            return;

        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();

        if(modifiers & Qt::ShiftModifier)
            keyInt += Qt::SHIFT;
        if(modifiers & Qt::ControlModifier)
            keyInt += Qt::CTRL;
        if(modifiers & Qt::AltModifier)
            keyInt += Qt::ALT;
        if(modifiers & Qt::MetaModifier)
            keyInt += Qt::META;

        translateKeySequence = QKeySequence(keyInt);
        keySequenceField->setText(translateKeySequence.toString());

        isClicked = false;

        labelAfterButton->setVisible(false);
    }

}


