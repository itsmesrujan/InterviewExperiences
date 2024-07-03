#ifndef CUSTOMFRAME_H
#define CUSTOMFRAME_H

#include <QFrame>
#include <QPixmap>

QT_BEGIN_NAMESPACE
  extern Q_WIDGETS_EXPORT void qt_blurImage( QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0 );
QT_END_NAMESPACE

class CustomFrame : public QFrame
{
public:
    explicit CustomFrame(QWidget *parent);

    void updateBackgroundImage(const QString szImage);

protected:
    void paintEvent(QPaintEvent * pe);

private:
    QPixmap m_pixmap;
    QImage applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent = 0);
};

#endif // CUSTOMFRAME_H
