#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QKeySequence>
#include <QPushButton>
#include <QGroupBox>
#include <QJsonDocument>
#include <QJsonObject>

#include "textfiledownloader.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QKeySequence defaultKeySeq,
                   const QString& apiKey,
                   QWidget* parent = nullptr);

    QKeySequence getCurrentKeySequence()   const;
    QString      getShortSourceLang()      const;
    QString      getShortTranslationLang() const;
    QString      getSourceLang()           const;
    QString      getTranslationLang()      const;

signals:
    void keySequenceChanged();

protected:
    void keyPressEvent(QKeyEvent*) override;

private:
    QGroupBox*  langGBox;
    QGroupBox*  keySequenceGBox;
    inline void createLangGroupBox();
    inline void createKeySequenceGroupBox();

    QComboBox*  translationLangBox;
    QComboBox*  sourceLangBox;

    QJsonDocument       document;
    QJsonObject         langList;
    TextFileDownloader* downloader;
    QString             APIkey;

    QLineEdit*   keySequenceField;
    QKeySequence keySequence;
    bool         isClicked;
    QLabel*      labelAfterButton;


};

#endif // SETTINGSDIALOG_H
