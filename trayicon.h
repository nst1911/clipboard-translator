#ifndef TRAYICON_H
#define TRAYICON_H

#include "translationdownloader.h"
#include <QAction>
#include <QDialog>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QKeySequence>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHotkey>

class KeySequenceDialog;

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    TrayIcon();

public slots:
    void translate();

private:
    QAction* setKeySequence;
    QAction* quit;

    QMenu* trayIconMenu;

    KeySequenceDialog* setDialog;
    QHotkey hotkey;

    TranslationDownloader* downloader;
};

class KeySequenceDialog : public QDialog {
    Q_OBJECT

public:
    explicit KeySequenceDialog(QKeySequence translateKeySequence);

    QKeySequence getKeySequence() const { return keySequence; }

signals:
    void keySequenceChanged();

protected:
    void keyPressEvent(QKeyEvent*) override;

private:
    QLabel* labelBeforeField;
    QLineEdit* keySequenceField;
    QLabel* labelAfterButton;

    QKeySequence keySequence;

    QPushButton* setButton;
    bool isClicked;
};

#endif // TRAYICON_H
