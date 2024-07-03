#ifndef CUSTOMTOOLBUTTON_H
#define CUSTOMTOOLBUTTON_H

#include <QtWidgets/QWidget>
#include <QToolButton>
#include <QLabel>
#include "custommenu.h"

class CustomToolButton: public QToolButton
{
    Q_OBJECT
public:
    explicit CustomToolButton(QString szToolBtnText, QStringList szMenuList, QIcon icon, QWidget *parent = nullptr);
    explicit CustomToolButton(QString szToolBtnText, QWidget *parent = nullptr);

    inline bool isMenuSet() {   return m_bMenuSet;  }

signals:
    void sigDisplayPopUp(QString szMsg);
    void sigMenuClosed();

public slots:
    void slotMenuActionClicked();
    void slotMenuAboutToDisplay(bool bIstrue);
    void slotMenuClosed();

protected:

private:
    CustomMenu *m_sampleMenu;
    QLabel *m_menuItemLbl;
    bool m_bMenuSet;
    void setDefaultProperties(QString szText = "");
};

#endif // CUSTOMTOOLBUTTON_H
