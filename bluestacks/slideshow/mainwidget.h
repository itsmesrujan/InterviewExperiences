#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QXmlStreamReader>
#include <QMap>
#include <QComboBox>
#include "customframe.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

signals:

public slots:
        void slotDisplayPopUp(QString szMsg);

private slots:
    void slotToolBtnClicked();
    void slotSetBackgroundImage(QString szCurrImage);

private:
    QMap<QString, QString> m_countryMap;
    QComboBox * m_countryCBox;
    CustomFrame *m_parentFrame;

    void createMainWidgetUI();
    void parseXMLFile();
    void parseCountry(QXmlStreamReader &xml);
    void updateCountryComboBox();
};

#endif // MAINWIDGET_H
