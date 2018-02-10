#include "popupwindow.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QImage>
#include <QVBoxLayout>
#include <QDebug>

PopUpWindow::PopUpWindow(int duration, QWidget *parent)
    : QFrame(parent),
      m_duration(duration)
{
    /* Widget initialization */

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setFrameStyle(QFrame::Box | QFrame::Raised);

    setMouseTracking(true);

    QRect availableGeometry = QApplication::desktop()->availableGeometry();
    resize(availableGeometry.width()/6, availableGeometry.height()/3);
    // Moving the window in the right bottom corner
    setGeometry(availableGeometry.width() - width() + availableGeometry.x(),
                availableGeometry.height() - height() + availableGeometry.y(),
                width(),
                height());

    sourceTextWidget      = new QTextEdit(this);
    sourceTextWidget->setReadOnly(true);
    sourceTextWidget->setFrameStyle(QFrame::Box | QFrame::Raised);
    resultTextWidget = new QTextEdit(this);
    resultTextWidget->setReadOnly(true);
    resultTextWidget->setFrameStyle(QFrame::Box | QFrame::Raised);

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
    layout->addWidget(sourceTextWidget);
    layout->addWidget(arrowImage,0,Qt::AlignCenter);
    layout->addWidget(resultTextWidget);
    layout->addWidget(yandexLabel);

    /* Animation initialization */

    animation.setTargetObject(this);
    animation.setPropertyName("opacity");
    connect(&animation, &QAbstractAnimation::finished, this, [this]() {
        if (getOpacity() == 0.0)
            QWidget::hide();
    });

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PopUpWindow::hideAnimation);
}

PopUpWindow::~PopUpWindow() {
    delete image;
}

void PopUpWindow::show()
{
    QWidget::show();

    languagesLabel->setText("<b>" + sourceLang + "</b> -> <b>" + resultLang + "</b>");

    setWindowOpacity(0.0);

    animation.setDuration(500);
    animation.setStartValue(0.0);
    animation.setEndValue(1.0);

    animation.start();

    timer->start(m_duration);
}

void PopUpWindow::hideAnimation() {

    timer->stop();

    animation.setDuration(500);
    animation.setStartValue(1.0);
    animation.setEndValue(0.0);

    animation.start();
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
    sourceTextWidget->setText(text);
    sourceLang = language;

}

void PopUpWindow::setResultText(const QString& text, const QString& language)
{
    resultTextWidget->setText(text);
    resultLang = language;
}

bool PopUpWindow::event(QEvent* e)
{
    if (e->type() == QEvent::Enter)
        timer->stop();
    if (e->type()==QEvent::Leave)
        timer->start(m_duration/3);

    return QWidget::event(e);
}





