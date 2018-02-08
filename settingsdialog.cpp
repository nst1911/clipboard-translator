#include "settingsdialog.h"
#include <QGridLayout>
#include <QtGui>

// Посмотреть пример SystemTrayIcon с доков Qt

SettingsDialog::SettingsDialog(QKeySequence keySeq, QWidget* parent)
    : QDialog(parent), keySequence(keySeq)
{
    createLangGroupBox();
    createKeySequenceGroupBox();

    QPushButton* closeButton = new QPushButton(tr("&Close"),this);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(langGBox,0,0);
    layout->addWidget(keySequenceGBox,0,1,1,1,Qt::AlignTop);
    layout->addWidget(closeButton,1,1);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

    setWindowTitle("Settings");

    resize(300,400);
}

void SettingsDialog::createLangGroupBox() {
    langGBox = new QGroupBox("Languages",this);

    QLabel* sourceLangLabel = new QLabel(tr("Source language:"),langGBox);
    sourceLangBox = new QComboBox(langGBox);
    sourceLangBox->setEditable(true);

    QLabel* translationLangLabel = new QLabel(tr("Translation language:"),langGBox);
    translationLangBox = new QComboBox(langGBox);
    translationLangBox->setEditable(true);

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
    layout->addWidget(translationLangBox, 3,1);

    langGBox->setLayout(layout);
}

void SettingsDialog::createKeySequenceGroupBox() {
    keySequenceGBox = new QGroupBox("Key sequence",this);

    QLabel* labelBeforeField = new QLabel(tr("Current shortcut: "), this);

    keySequenceField = new QLineEdit(keySequence.toString(), this);
    keySequenceField->setReadOnly(true);

    QPushButton* setButton = new QPushButton(tr("&Enter new shortcut"),this);

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
    layout->setSizeConstraint(QLayout::SetFixedSize);
    keySequenceGBox->setLayout(layout);
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
