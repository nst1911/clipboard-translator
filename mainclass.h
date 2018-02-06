#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QObject>
#include "trayicon.h"
#include "translationdownloader.h"
#include "keysequencedialog.h"
#include <QHotkey>
#include <QMainWindow>

class MainClass : public QMainWindow
{
    Q_OBJECT
public:
    MainClass();
    void setVisible(bool) override;

public slots:
    void translate();

private:
    TrayIcon* trayIcon;

    KeySequenceDialog* setDialog;
    QHotkey hotkey;

    TranslationDownloader* downloader;
};

#endif // MAINCLASS_H
