#include "customframe.h"
#include <QPainter>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsBlurEffect>

CustomFrame::CustomFrame(QWidget *parent) : QFrame(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    updateBackgroundImage(":/images/game-war-bg.jpg");
}

void CustomFrame::updateBackgroundImage(const QString szImage)
{
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(10);
    QImage source(szImage);
    QImage result = applyEffectToImage(source, blur);
    m_pixmap.convertFromImage(result);
    resize(m_pixmap.size());
}

void CustomFrame::paintEvent(QPaintEvent *pe)
{
    Q_UNUSED(pe);
    QPainter paint(this);
    paint.drawPixmap(0, 0, width(), height(), m_pixmap);
}

QImage CustomFrame::applyEffectToImage(QImage srcImage, QGraphicsEffect *effect, int extent)
{
    if(srcImage.isNull()) return QImage();
    if(!effect) return srcImage;
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(srcImage));
    item.setGraphicsEffect(effect);
    scene.addItem(&item);
    QImage res(srcImage.size()+QSize(extent*2, extent*2), QImage::Format_ARGB32);
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF( -extent, -extent, srcImage.width()+extent*2, srcImage.height()+extent*2 ) );
    return res;
}
