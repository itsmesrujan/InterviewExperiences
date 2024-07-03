#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QHoverEvent>
#include <QLabel>
#include <QEventLoop>

#include "customtoolbutton.h"

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QString szBtnName, QString szBtnDesc, QStringList szMenuList, QWidget *parent = nullptr);

signals:
    void sigDisplayPopUp(QString);
    void sigUserHovered(bool);

public slots:
    void slotToolBtnClicked();
    void slotDisplayPopUp(QString szMsg);
    void slotMenuClosed();

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    bool event(QEvent *e);

private:
    QLabel *m_borderLabel;
    QLabel *m_appIconLbl;
    QPixmap m_highlightedImage;
    QPixmap m_nonHighlightedImage;
    CustomToolButton *m_appsToolBtn;
    QEventLoop m_eventLoop;
    void hoverEnter(QHoverEvent *he);
    void hoverLeave(QHoverEvent *he);
    void hoverMove(QHoverEvent *he);
    void setHighlight();
    void unsetHighlight();
};

#endif // CUSTOMWIDGET_H
