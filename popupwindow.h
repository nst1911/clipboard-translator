#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QTimer>
#include <QFrame>
#include <QLabel>
#include <QTextEdit>

class PopUpWindow : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(float opacity READ getOpacity WRITE setOpacity)

    void  setOpacity(float opacity);
    float getOpacity() const;

public:
    explicit PopUpWindow(QWidget *parent = nullptr);
    virtual ~PopUpWindow();

    void setSourceText(const QString& text, const QString& language);
    void setTranslationText(const QString& text, const QString& language);

public slots:
    void show();

private slots:
    void hideAnimation();
    void hide();

private:   
    QTextEdit* sourceText;
    QTextEdit* translationText;
    QLabel* languagesLabel;
    QString sourceLang, translationLang;
    QImage* image;

    QPropertyAnimation animation;
    float opacity;
    QTimer* timer;
};

#endif // POPUPWINDOW_H
