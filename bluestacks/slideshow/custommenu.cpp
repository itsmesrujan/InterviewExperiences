#include "custommenu.h"
#include <QDebug>

CustomMenu::CustomMenu(QWidget *parent) : QMenu (parent)
{
    QString szMenuStyle = "QMenu {background-color: #000033; width:150px;}"\
                          "QMenu::item {background-color: #000033;}"\
                          "QMenu::indicator{image: none;}"\
                          "QMenu::separator{background:#81D3EC;height: 1px;margin-left: 5px;margin-right: 5px;}";
    setFocusPolicy(Qt::NoFocus);
    setStyleSheet(szMenuStyle);
    setAttribute(Qt::WA_Hover);
    setMouseTracking(true);
}

void CustomMenu::showEvent(QShowEvent *e)
{
    QPoint currPoint = this->pos();
    this->move(currPoint.x()+35, currPoint.y()+30);
    QMenu::showEvent(e);
}

void CustomMenu::leaveEvent(QEvent *event)
{
    this->close();
    emit sigMenuClosed();
    QMenu::leaveEvent(event);
}

void CustomMenu::hideEvent(QHideEvent *event)
{
    emit sigMenuClosed();
    QMenu::hideEvent(event);
}
