#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class CustomLabel : public QLabel
{
public:
    explicit CustomLabel(QString szLblText, QWidget *parent = nullptr);

protected:
    void enterEvent(QEvent *event) {
        Q_UNUSED(event)
        this->setStyleSheet("background-color: #000033; color:#81D3EC; margin-left: 5px;margin-right: 5px;margin-top:2px;margin-bottom:2px;");
    }
    void leaveEvent(QEvent *event) {
        Q_UNUSED(event)
        this->setStyleSheet(m_szDefaultLabelStylesheet);
    }

private:
    const QString m_szDefaultLabelStylesheet ="background-color: #000033; color:white; margin-left: 5px;margin-right: 5px;margin-top:2px;margin-bottom:2px;";
};

#endif // CUSTOMLABEL_H
