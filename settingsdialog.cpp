#include "settingsdialog.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>

SettingsDialog::SettingsDialog(QKeySequence defaultKeySeq,
                               const QString& apiKey,
                               QWidget* parent)
    : QDialog(parent),
      APIkey(apiKey),
      keySequence(defaultKeySeq)
{
    createLangGroupBox();
    createKeySequenceGroupBox();
    createOtherSettingsGBox();

    QPushButton* closeButton = new QPushButton(tr("&Close"),this);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(langGBox);
    layout->addWidget(keySequenceGBox);
    layout->addWidget(otherSettingsGBox);
    layout->addWidget(closeButton);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

    setWindowTitle("Settings");

    QRect availableGeometry = QApplication::desktop()->availableGeometry();
    resize(availableGeometry.width()/4, availableGeometry.height()/1.5);
}

void SettingsDialog::createLangGroupBox() {
    langGBox = new QGroupBox("Languages",this);

    QLabel* sourceLangLabel = new QLabel(tr("Source language:"),langGBox);
    sourceLangBox = new QComboBox(langGBox);
    sourceLangBox->setEditable(true);

    QLabel* translationLangLabel = new QLabel(tr("Result language:"),langGBox);
    resultLangBox = new QComboBox(langGBox);
    resultLangBox->setEditable(true);

    QLabel* translatorLinkLabel =
            new QLabel(tr("Suggested languages are provided <br>by <a href=\"https://translate.yandex.ru/\">Yandex.Translator</a><br>"),langGBox);
    translatorLinkLabel->setTextFormat(Qt::RichText);
    translatorLinkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    translatorLinkLabel->setOpenExternalLinks(true);

    QGridLayout* layout = new QGridLayout(langGBox);
    layout->addWidget(translatorLinkLabel,0,0,2,2);
    layout->addWidget(sourceLangLabel,2,0);
    layout->addWidget(sourceLangBox, 2,1);
    layout->addWidget(translationLangLabel,3,0);
    layout->addWidget(resultLangBox, 3,1);
    langGBox->setLayout(layout);

    /* Downloading list of available languages from translating service */

    downloader = new TextFileDownloader;
    downloader->dataRequest("https://translate.yandex.net/api/v1.5/tr.json/getLangs"
                            "?key=" + APIkey +
                            "&ui=en");

    connect(downloader, &TextFileDownloader::readyToRead, this, [this]() {
        document = QJsonDocument::fromJson(downloader->getData().toUtf8());
        langList = document.object().value("langs").toObject();

        foreach (const QString& key, langList.keys()) {
            /* The first argument (text) is the full language name ("English"),
            /* the second (userData) is the short one ("en") */
            sourceLangBox->addItem(langList.value(key).toString(), key);
            resultLangBox->addItem(langList.value(key).toString(), key);
        }
    });

}

void SettingsDialog::createKeySequenceGroupBox() {
    keySequenceGBox = new QGroupBox("Key sequence",this);

    QLabel* labelBeforeField = new QLabel(tr("Current shortcut: "), this);

    keySequenceField = new QLineEdit(keySequence.toString(), this);
    keySequenceField->setReadOnly(true);

    QPushButton* setButton = new QPushButton(tr("&Enter new shortcut"),this);

    /* This label is appeared after clicking on the button */
    labelAfterButton = new QLabel(tr("Press any combination of keys (Ctrl+Shift+D, Alt+5, ...)\n"
                          "Several combinations may not work on your operation system."),this);
    labelAfterButton->setVisible(false);

    connect(setButton,&QPushButton::clicked,
            this, [this]() { isClicked = true; labelAfterButton->setVisible(true); }
    );

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(labelBeforeField,0,0);
    layout->addWidget(keySequenceField,0,1);
    layout->addWidget(setButton,1,1);
    layout->addWidget(labelAfterButton,2,0,1,2);
    keySequenceGBox->setLayout(layout);
}

void SettingsDialog::createOtherSettingsGBox() {
    otherSettingsGBox = new QGroupBox("Other settings",this);

    QLabel* popUpDurationLabel = new QLabel("Pop-up notification duration:",this);
    popUpDuration = new QSpinBox(this);
    popUpDuration->setValue(4);
    popUpDuration->setMinimum(1);

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(popUpDurationLabel,0,0);
    layout->addWidget(popUpDuration,0,1);
    otherSettingsGBox->setLayout(layout);
}

void SettingsDialog::keyPressEvent(QKeyEvent* keyEvent) {
    if (!isClicked)
        QDialog::keyPressEvent(keyEvent);
    else {
        int keyInt = keyEvent->key();

        if (keyInt == Qt::Key_unknown) return;

        // Only single click of modifier
        if (keyInt == Qt::Key_Control || keyInt == Qt::Key_Shift   ||
            keyInt == Qt::Key_Alt     || keyInt == Qt::Key_Meta)
            return;

        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();

        if(modifiers & Qt::ShiftModifier)
            keyInt += Qt::SHIFT;
        if(modifiers & Qt::ControlModifier)
            keyInt += Qt::CTRL;
        if(modifiers & Qt::AltModifier)
            keyInt += Qt::ALT;
        if(modifiers & Qt::MetaModifier)
            keyInt += Qt::META;

        keySequence = QKeySequence(keyInt);
        keySequenceField->setText(keySequence.toString());

        isClicked = false;
        labelAfterButton->setVisible(false);

        emit keySequenceChanged();
    }
}
