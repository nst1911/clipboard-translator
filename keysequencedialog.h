#ifndef KEYSEQUENCEDIALOG_H
#define KEYSEQUENCEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QKeySequence>
#include <QPushButton>

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
    friend class MainClass;

    QLabel* labelBeforeField;
    QLineEdit* keySequenceField;
    QLabel* labelAfterButton;

    QKeySequence keySequence;

    QPushButton* setButton;
    bool isClicked;
};

#endif // KEYSEQUENCEDIALOG_H
