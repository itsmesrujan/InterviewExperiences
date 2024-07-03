#include "customlabel.h"

CustomLabel::CustomLabel(QString szLblText, QWidget *parent):QLabel(parent)
{
    setText(szLblText);
    setWordWrap(true);
    setFont(QFont("Times", 8, QFont::Bold));
    setStyleSheet(m_szDefaultLabelStylesheet);
    setMinimumHeight(30);
    setCursor(Qt::PointingHandCursor);
    setAttribute(Qt::WA_Hover);
    setMouseTracking(true);
}
