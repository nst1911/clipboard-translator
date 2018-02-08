#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QObject>
#include "trayicon.h"
#include "settingsdialog.h"
#include "textfiledownloader.h"
#include <QHotkey>

class MainClass : public QWidget
{
    Q_OBJECT

public:
    MainClass();
    void setVisible(bool) override;

public slots:
    void translate();

private:
    TrayIcon* trayIcon;
    SettingsDialog* settingsDialog;
    QHotkey hotkey;

    QString APIkey, language;
    TextFileDownloader* downloader;
};

#endif // MAINCLASS_H
