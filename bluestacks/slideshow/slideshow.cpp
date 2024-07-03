#include <QBasicTimer>
#include <QList>
#include <QImage>
#include <QDir>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

#include "slideshow.h"

class SlideShowPrivate
{
public:
    SlideShowPrivate();

    int currentSlide;
    int slideInterval;
    QBasicTimer interSlideTimer;
    QStringList imagePaths;

    void showNextSlide();
};

SlideShowPrivate::SlideShowPrivate()
{
    currentSlide = 0;
    slideInterval = 5000; // Default to 5 sec interval
}

void SlideShowPrivate::showNextSlide()
{
    currentSlide++;
    if (currentSlide >= imagePaths.size())
        currentSlide = 0;
}

SlideShow::SlideShow(QWidget* parent) :
    QWidget(parent)
{
    slideShowMainObj = new SlideShowPrivate;

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAttribute(Qt::WA_StaticContents, true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setMouseTracking(true);
    setWindowState(this->windowState()|Qt::WindowMaximized);

    addImageDir(":/images/");
}

SlideShow::~SlideShow()
{
    delete slideShowMainObj;
}

void SlideShow::addImageDir(QString dirName)
{
    QDir dir(dirName);

    QStringList fileNames = dir.entryList(QDir::Files | QDir::Readable, QDir::Name);

    for (int i=0; i<fileNames.count(); i++) {
        slideShowMainObj->imagePaths << dir.absoluteFilePath(fileNames[i]);
    }
}

void SlideShow::addImage(QString filename)
{
    slideShowMainObj->imagePaths << filename;
}

void SlideShow::clearImages()
{
    slideShowMainObj->imagePaths.clear();
}

void SlideShow::startShow()
{
    slideShowMainObj->interSlideTimer.start(slideShowMainObj->slideInterval, this);
    slideShowMainObj->showNextSlide();
    update();
}

void SlideShow::stopShow()
{
    slideShowMainObj->interSlideTimer.stop();
}

int SlideShow::slideInterval()
{
    return slideShowMainObj->slideInterval;
}

void SlideShow::setSlideInterval(int val)
{
    slideShowMainObj->slideInterval = val;
}

void SlideShow::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    slideShowMainObj->showNextSlide();
    emit sigImageChanged(slideShowMainObj->imagePaths[slideShowMainObj->currentSlide]);

    update();
}

void SlideShow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    if (slideShowMainObj->imagePaths.size() > 0) {
        QPixmap slide = QPixmap(slideShowMainObj->imagePaths[slideShowMainObj->currentSlide]);
        QSize slideSize = slide.size();
        QSize scaledSize = QSize(qMin(slideSize.width(), size().width()),
                                 qMin(slideSize.height(), size().height()));

        if (slideSize != scaledSize)
            slide = slide.scaled(scaledSize, Qt::IgnoreAspectRatio);

        QRect pixmapRect(qMax( (size().width() - slide.width())/2, 0),
                         qMax( (size().height() - slide.height())/2, 0),
                         slide.width(),
                         slide.height());

        // Fill in top & bottom rectangles:
        painter.fillRect(0, 0, size().width(), pixmapRect.top(), Qt::transparent);
        painter.fillRect(0, pixmapRect.bottom(), size().width(), size().height(), Qt::transparent);

        if (pixmapRect.left() > 0) {
            // Fill in left & right rectangles:
            painter.fillRect(0, 0, pixmapRect.left(), size().height(), Qt::transparent);
            painter.fillRect(pixmapRect.right(), 0, size().width(), size().height(), Qt::transparent);
        }

        painter.drawPixmap(pixmapRect, slide);
    } else
        painter.fillRect(event->rect(), Qt::transparent);
}

void SlideShow::keyPressEvent(QKeyEvent* event)
{
    Q_UNUSED(event);
    emit inputReceived();
}

void SlideShow::mouseMoveEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    emit inputReceived();
}

void SlideShow::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    emit inputReceived();
}

void SlideShow::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    emit inputReceived();
}

void SlideShow::showEvent(QShowEvent * event )
{
    Q_UNUSED(event);
#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor);
#endif
}
