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
#include <QSpinBox>

#include "textfiledownloader.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    // Key sequence for translating; API key of translating service
    SettingsDialog(QKeySequence defaultKeySeq,
                   const QString& apiKey,
                   QWidget* parent = nullptr);

    inline QKeySequence getCurrentKeySequence()   const { return keySequence; }
    // Short type of language word (for example, "en")
    inline QString      getShortSourceLang()      const { return sourceLangBox->currentData().toString(); }
    inline QString      getShortResultLang()      const { return resultLangBox->currentData().toString(); }
    // Full language word (for example, "English")
    inline QString      getSourceLang()           const { return sourceLangBox->currentText(); }
    inline QString      getTranslationLang()      const { return resultLangBox->currentText(); }
    inline int          getPopUpDuration()        const { return popUpDuration->value(); }

signals:
    void keySequenceChanged();

protected:
    void keyPressEvent(QKeyEvent*) override;

private:
    QGroupBox*  langGBox;
    QGroupBox*  keySequenceGBox;
    QGroupBox*  otherSettingsGBox;
    inline void createLangGroupBox();
    inline void createKeySequenceGroupBox();
    inline void createOtherSettingsGBox();

    QComboBox*  resultLangBox;
    QComboBox*  sourceLangBox;

    QSpinBox*   popUpDuration;

    /* Parsing result from translating service */
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
