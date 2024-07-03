#ifndef CUSTOMMENU_H
#define CUSTOMMENU_H

#include <QMenu>

class CustomMenu : public QMenu
{
    Q_OBJECT
public:
    explicit CustomMenu(QWidget *parent=nullptr);

signals:
    void sigMenuClosed();

public slots:

protected:
    void showEvent(QShowEvent *e);
    void leaveEvent(QEvent *event);
    void hideEvent(QHideEvent *event);
};

#endif // CUSTOMMENU_H
