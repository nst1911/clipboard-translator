#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QWidget>
#include <QHotkey>
#include <QSystemTrayIcon>
#include <QMenu>

#include "settingsdialog.h"
#include "popupwindow.h"
#include "textfiledownloader.h"

class MainClass : public QWidget
{
    Q_OBJECT

public:
    MainClass();
    void setVisible(bool) override;

public slots:
    void translate();

private:
    QSystemTrayIcon* trayIcon;
    QMenu*   trayIconMenu;
    QAction* settings;
    QAction* about;
    QAction* quit;
    void     createTrayIcon();

    SettingsDialog* settingsDialog;
    QDialog*        aboutDialog;
    void            createAboutDialog();

    PopUpWindow* popUp;

    QHotkey hotkey;

    QString APIkey; // API key of translating service
    QString dataFileName;
    TextFileDownloader* downloader;
};

#endif // MAINCLASS_H
