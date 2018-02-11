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
    friend class MainClass; // getting access to keySequenceField

    // Key sequence for translating; API key of translating service
    SettingsDialog(const QString& fileName,
                   const QString& apiKey,
                   QWidget* parent = nullptr);

    inline QKeySequence getCurrentKeySequence()   const { return QKeySequence(keySequenceField->text()); }
    // Short type of language word (for example, "en")
    inline QString      getShortSourceLang()      const { return sourceLangBox->currentData().toString(); }
    inline QString      getShortResultLang()      const { return resultLangBox->currentData().toString(); }
    // Full language word (for example, "English")
    inline QString      getSourceLang()           const { return sourceLangBox->currentText(); }
    inline QString      getTranslationLang()      const { return resultLangBox->currentText(); }
    inline int          getPopUpDuration()        const { return popUpDuration->value(); }

public slots:
    void serialize();
    void deserialize();
    void setDefaultValues();

signals:
    void readyToDeserialize();
    void deserialized();

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

    QString serializationFileName;

    QLineEdit*   keySequenceField;
    bool         isClicked; // if button setting key sequence isn't clicked, keyPressEvent works as it does in the base class
    QLabel*      labelAfterButton;
};

#endif // SETTINGSDIALOG_H
