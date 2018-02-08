#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QKeySequence>
#include <QPushButton>
#include <QGroupBox>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QKeySequence keySeq,QWidget* parent = nullptr);
    QKeySequence getKeySequence() const { return keySequence; }

signals:
   void keySequenceChanged();

protected:
    void keyPressEvent(QKeyEvent*) override;

private:
    QGroupBox* langGBox;
    QGroupBox* keySequenceGBox;
    inline void createLangGroupBox();
    inline void createKeySequenceGroupBox();

    QComboBox* translationLangBox;
    QComboBox* sourceLangBox;

    QLineEdit* keySequenceField;
    QKeySequence keySequence;
    bool isClicked;
    QLabel* labelAfterButton;


};

#endif // SETTINGSDIALOG_H
