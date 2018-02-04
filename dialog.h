#ifndef DIALOG_H
#define DIALOG_H

#include <QSystemTrayIcon>
#include <QDialog>
#include <QAction>
#include <QSystemTrayIcon>
#include <QMenu>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog();
    void setVisible(bool visible) override;

private:
    QAction* minimize;
    QAction* restore;
    QAction* quit;

    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;

    void createActions();
    void createTrayIcon();
};

#endif // DIALOG_H
