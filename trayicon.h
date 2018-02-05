#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QDialog>
#include <QAction>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QKeySequence>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    TrayIcon();

private:
    QAction* setKeySequence;
    QAction* quit;

    QKeySequence translateKeySequence;

    QMenu* trayIconMenu;
};

class KeySequenceDialog : public QDialog {
    Q_OBJECT

public:
    KeySequenceDialog();
};

#endif // TRAYICON_H
