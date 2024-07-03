#include "customwidget.h"
#include "customlabel.h"

#include <QVBoxLayout>
#include <QVariantMap>
#include <QPainter>

CustomWidget::CustomWidget(QString szBtnName, QString szBtnDesc, QStringList szMenuList,
                           QWidget *parent) : QWidget(parent), m_borderLabel(nullptr), m_appIconLbl(nullptr),
    m_highlightedImage(QPixmap()), m_nonHighlightedImage(QPixmap()), m_appsToolBtn(nullptr)
{
    QFont menuFont("Times",11, QFont::Bold);
    QVBoxLayout *appsVBLayout = new QVBoxLayout(this);
    appsVBLayout->setSpacing(0);

    if (szMenuList.isEmpty())
        m_appsToolBtn = new CustomToolButton(szBtnName, this);
    else
        m_appsToolBtn = new CustomToolButton(szBtnName, szMenuList, QIcon(":/resources/white-arrow-down.png"), this);

    m_appsToolBtn->setObjectName(szBtnDesc);
    m_appsToolBtn->setFont(menuFont);
    connect(m_appsToolBtn, SIGNAL(clicked()), this, SLOT(slotToolBtnClicked()));
    connect(m_appsToolBtn, SIGNAL(sigDisplayPopUp(QString)), this, SLOT(slotDisplayPopUp(QString)));
    connect(this, SIGNAL(sigUserHovered(bool)), m_appsToolBtn, SLOT(slotMenuAboutToDisplay(bool)));
    connect(m_appsToolBtn, SIGNAL(sigMenuClosed()), this, SLOT(slotMenuClosed()));
    appsVBLayout->addWidget(m_appsToolBtn, 0, Qt::AlignCenter|Qt::AlignBottom);

    m_appIconLbl = new QLabel(this);
    m_appIconLbl->setMargin(0);
    if (!szMenuList.isEmpty()) {
        QVariantMap variantMap;
        variantMap.insert("color",QColor(129,211,236));

        m_nonHighlightedImage = QPixmap(":/resources/white-arrow-down.png");
        m_highlightedImage = m_nonHighlightedImage;
        QPainter painter(&m_highlightedImage);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(m_highlightedImage.rect(), QColor(129,211,236));
        painter.end();
        m_appIconLbl->setPixmap(m_nonHighlightedImage.scaled(25, 25, Qt::KeepAspectRatio));
    }

    appsVBLayout->addWidget(m_appIconLbl, 0, Qt::AlignCenter|Qt::AlignTop);

    m_borderLabel = new QLabel(this);
    m_borderLabel->setStyleSheet("background-color: none;height:1px;");
    m_borderLabel->setFixedHeight(2);
    m_borderLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    appsVBLayout->addWidget(m_borderLabel);

    this->setAttribute(Qt::WA_Hover);
    this->setMouseTracking(true);
    this->setObjectName(szBtnName);
    this->setLayout(appsVBLayout);
}

void CustomWidget::slotMenuClosed()
{
    unsetHighlight();
}

void CustomWidget::slotToolBtnClicked()
{
    QToolButton *toolBtn = dynamic_cast<QToolButton *>(this->sender());
    if (toolBtn){
        if (!toolBtn->objectName().isEmpty()){
            emit sigDisplayPopUp(toolBtn->objectName());
            unsetHighlight();
        }
    }
}

void CustomWidget::slotDisplayPopUp(QString szMsg)
{
    unsetHighlight();
    emit sigDisplayPopUp(szMsg);
}

void CustomWidget::enterEvent(QEvent *event)
{
    emit sigUserHovered(true);
    setHighlight();
//    QWidget::event(event);

    // Check if the event is actually QEnterEvent
    if (event->type() == QEvent::Enter) {
        QEnterEvent *enterEvent = dynamic_cast<QEnterEvent*>(event);
        if (enterEvent) {
            // Call your handling function with QEnterEvent*
            QWidget::event(enterEvent);
        }
    }
}

void CustomWidget::leaveEvent(QEvent *event)
{
    unsetHighlight();
    QWidget::leaveEvent(event);
}

bool CustomWidget::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent *>(e));
        return  true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent *>(e));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent *>(e));
        return true;
        break;
    default:
        break;
    }
    return  QWidget::event(e);
}

void CustomWidget::hoverEnter(QHoverEvent *he)
{
    Q_UNUSED(he)
    emit sigUserHovered(true);

    if (m_appsToolBtn)
        if (!m_appsToolBtn->isMenuSet())
            setHighlight();
}

void CustomWidget::hoverLeave(QHoverEvent *he)
{
    Q_UNUSED(he)
    unsetHighlight();
}

void CustomWidget::hoverMove(QHoverEvent *he)
{
    Q_UNUSED(he)
    if (m_appsToolBtn)
        if (!m_appsToolBtn->isMenuSet())
            setHighlight();
}

void CustomWidget::setHighlight()
{
    if (m_appsToolBtn)
        m_appsToolBtn->setStyleSheet("color:#81D3EC;");
    if (m_borderLabel)
        m_borderLabel->setStyleSheet("background-color: #81D3EC;height:1px;");
    if (m_appIconLbl)
        m_appIconLbl->setPixmap(m_highlightedImage.scaled(25, 25, Qt::KeepAspectRatio));
}

void CustomWidget::unsetHighlight()
{
    if (m_appsToolBtn)
        m_appsToolBtn->setStyleSheet("color:white;");
    if (m_borderLabel)
        m_borderLabel->setStyleSheet("background-color: none;height:1px;");
    if (m_appIconLbl)
        m_appIconLbl->setPixmap(m_nonHighlightedImage.scaled(25, 25, Qt::KeepAspectRatio));
}
