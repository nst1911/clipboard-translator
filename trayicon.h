#ifndef TRAYICON_H
#define TRAYICON_H

#include <QAction>
#include <QDialog>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QKeySequence>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class KeySequenceDialog;

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    TrayIcon();

private:
    QAction* setKeySequence;
    QAction* quit;

    QMenu* trayIconMenu;

    KeySequenceDialog* setDialog;
};

class KeySequenceDialog : public QDialog {
    Q_OBJECT

public:
    explicit KeySequenceDialog(QKeySequence keySequence);

    QKeySequence getTranslateKeySequence() const { return translateKeySequence; }

protected:
    void keyPressEvent(QKeyEvent*) override;

private:
    QLabel* labelBeforeField;
    QLineEdit* keySequenceField;
    QLabel* labelAfterButton;
    QPushButton* setButton;
    QKeySequence translateKeySequence;

    bool isClicked;
};

#endif // TRAYICON_H
