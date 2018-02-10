#include "popupwindow.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QImage>
#include <QVBoxLayout>

PopUpWindow::PopUpWindow(QWidget *parent) : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::Tool |
                   Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_ShowWithoutActivating);

    setFrameStyle(QFrame::Box | QFrame::Raised);

    QRect availableGeometry = QApplication::desktop()->availableGeometry();
    resize(availableGeometry.width()/6, availableGeometry.height()/3);
    setGeometry(availableGeometry.width() - width() + availableGeometry.x(),
                availableGeometry.height() - height() + availableGeometry.y(),
                width(),
                height());

    sourceText      = new QTextEdit(this);
    translationText = new QTextEdit(this);

    sourceText->setReadOnly(true);
    sourceText->setFrameStyle(QFrame::Box | QFrame::Raised);
    translationText->setReadOnly(true);
    translationText->setFrameStyle(QFrame::Box | QFrame::Raised);

    QLabel* arrowImage = new QLabel(this);
    image = new QImage(":/arrow.png");
    arrowImage->setPixmap(QPixmap::fromImage(*image));
    arrowImage->adjustSize();

    languagesLabel = new QLabel(this);
    languagesLabel->setTextFormat(Qt::RichText);

    QLabel* yandexLabel = new QLabel(this);
    yandexLabel->setTextFormat(Qt::RichText);
    yandexLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    yandexLabel->setOpenExternalLinks(true);
    yandexLabel->setText(tr("Powered by <a href=\"https://github.com/ntrsBIG/clipboard-translator\">Yandex.Translate</a>"));

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(languagesLabel,0, Qt::AlignCenter);
    layout->addWidget(sourceText);
    layout->addWidget(arrowImage,0,Qt::AlignCenter);
    layout->addWidget(translationText);
    layout->addWidget(yandexLabel);

    animation.setTargetObject(this);
    animation.setPropertyName("opacity");
    connect(&animation, &QAbstractAnimation::finished, this, &PopUpWindow::hide);

    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &PopUpWindow::hideAnimation);
}

PopUpWindow::~PopUpWindow() {
    delete image;
}

void PopUpWindow::show()
{
    languagesLabel->setText("<b>" + sourceLang + "</b> -> <b>" + translationLang + "</b>");
    setWindowOpacity(0.0);

    animation.setDuration(150);
    animation.setStartValue(0.0);
    animation.setEndValue(1.0);

    QWidget::show();

    animation.start();

    timer->start(4000);
}

void PopUpWindow::hideAnimation() {

    timer->stop();
    animation.setDuration(500);
    animation.setStartValue(1.0);
    animation.setEndValue(0.0);
    animation.start();
}

void PopUpWindow::hide()
{
    if (getOpacity() == 0.0)
        QWidget::hide();
}

void PopUpWindow::setOpacity(float op)
{
    opacity = op;
    setWindowOpacity(op);
}

float PopUpWindow::getOpacity() const
{
    return opacity;
}

void PopUpWindow::setSourceText(const QString& text, const QString& language)
{
    sourceText->setText(text);
    sourceLang = language;

}

void PopUpWindow::setTranslationText(const QString& text, const QString& language)
{
    translationText->setText(text);
    translationLang = language;
}





