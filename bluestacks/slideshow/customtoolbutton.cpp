#include "customtoolbutton.h"
#include "customlabel.h"
#include "custommenu.h"

#include <QWidgetAction>

CustomToolButton::CustomToolButton(QString szToolBtnText, QStringList szMenuList,
                                   QIcon icon, QWidget *parent) : QToolButton(parent), m_sampleMenu(nullptr),
    m_bMenuSet(false)
{
    setIcon(icon);
    setDefaultProperties(szToolBtnText);

    if ( !szMenuList.isEmpty() )
    {
        m_bMenuSet = true;
        m_sampleMenu = new CustomMenu(this);
        connect(m_sampleMenu, SIGNAL(sigMenuClosed()), this, SLOT(slotMenuClosed()));
        for ( int nIndex = 0; nIndex < szMenuList.size(); ++nIndex ) {
            QWidgetAction *sampleAction = new QWidgetAction(this);
            sampleAction->setObjectName(szMenuList[nIndex]);
            CustomLabel *menuItemLbl = new CustomLabel(szMenuList[nIndex], this);
            sampleAction->setDefaultWidget(menuItemLbl);
            connect(sampleAction, SIGNAL(triggered()), this, SLOT(slotMenuActionClicked()));
            m_sampleMenu->addAction(sampleAction);
            m_sampleMenu->addSeparator();
        }
        setMenu(m_sampleMenu);
    }
}

CustomToolButton::CustomToolButton(QString szToolBtnText, QWidget *parent) : QToolButton(parent)
{
    setDefaultProperties(szToolBtnText);
}

void CustomToolButton::slotMenuActionClicked()
{
    QWidgetAction *action = dynamic_cast<QWidgetAction *>(this->sender());
    if (action) {
        if (!action->objectName().isEmpty()) {
            emit sigDisplayPopUp(action->objectName());
        }
    }
}

void CustomToolButton::slotMenuAboutToDisplay(bool bIstrue)
{
    if (m_sampleMenu) {
        if(bIstrue)
            this->showMenu();
        else
            this->menu()->close();
    }
}

void CustomToolButton::slotMenuClosed()
{
    emit sigMenuClosed();
}

void CustomToolButton::setDefaultProperties(QString szText)
{
    setText(szText);
    setLayoutDirection(Qt::RightToLeft);
    setToolButtonStyle(Qt::ToolButtonTextOnly);
    setCursor(Qt::PointingHandCursor);
    setPopupMode(QToolButton::InstantPopup);
    setContentsMargins(0, 0, 0, 0);
    setStyleSheet("QToolButton{color:white; border-bottom: 3px solid #81D3EC;}");
    setAttribute(Qt::WA_Hover);
    setMouseTracking(true);
}
