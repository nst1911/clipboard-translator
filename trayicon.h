#ifndef TRAYICON_H
#define TRAYICON_H

#include <QAction>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QToolTip>


class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    TrayIcon(QObject* parent = nullptr);

private:
    friend class MainClass;
    QAction* settings;
    QAction* quit;

    QMenu* trayIconMenu;
};

#endif // TRAYICON_H
