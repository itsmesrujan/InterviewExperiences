#include "mainwidget.h"
#include "slideshow.h"
#include "customwidget.h"
#include "customframe.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QToolBar>
#include <QToolButton>
#include <QMessageBox>
#include <QDir>
#include <QPushButton>
#include <QListView>
#include <QPropertyAnimation>
#include <QProxyStyle>
#include <QLayout>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent), m_countryCBox(nullptr),
    m_parentFrame(nullptr)
{
    // Ui creation will happen here!
    createMainWidgetUI();
}

MainWidget::~MainWidget()
{
    if (m_countryCBox) {
        delete m_countryCBox;
        m_countryCBox= nullptr;
    }

    m_countryMap.clear();
}

void MainWidget::slotToolBtnClicked()
{
    QToolButton *toolBtn = dynamic_cast<QToolButton *>(this->sender());
    if (toolBtn){
        if (!toolBtn->objectName().isEmpty()){
            slotDisplayPopUp(toolBtn->objectName());
        }
    }
}

void MainWidget::slotSetBackgroundImage(QString szCurrImage)
{
    m_parentFrame->updateBackgroundImage(szCurrImage);
    m_parentFrame->update();
}

void MainWidget::createMainWidgetUI()
{
    QLayout *parentLayout = new QGridLayout(this);
    parentLayout->setContentsMargins(0,0,0,0);

    m_parentFrame = new CustomFrame(this);
    QVBoxLayout *vBoxLayout = new QVBoxLayout(m_parentFrame);
    vBoxLayout->setContentsMargins(0,0,0,0);
    vBoxLayout->setSpacing(0);

    QHBoxLayout *menuHBoxLayout = new QHBoxLayout(m_parentFrame);

    QToolBar *headertoolBar = new QToolBar;
    headertoolBar->setAllowedAreas(Qt::TopToolBarArea);
    headertoolBar->setStyleSheet("background-color:transparent;spacing:9px;");
    headertoolBar->setContentsMargins(15,15,20,5);

    QPixmap logoPixMap(":/resources/officialLogo.png");
    QLabel *iconLbl = new QLabel(m_parentFrame);
    iconLbl->setPixmap(logoPixMap.scaled(200, 200, Qt::KeepAspectRatio));
    iconLbl->setContentsMargins(10,10,5,5);
    headertoolBar->addWidget(iconLbl);

    QFont menuFont("Times",11, QFont::Bold);
    CustomWidget *appsWid = new CustomWidget("Apps","We have lot of apps supported!", QStringList(), m_parentFrame);
    connect(appsWid,SIGNAL(sigDisplayPopUp(QString)), this, SLOT(slotDisplayPopUp(QString)));
    headertoolBar->addWidget(appsWid);

    QStringList szStreamingMenuList;
    szStreamingMenuList << "WHAT IS BTV?"
               << "STREAM FOR BLUESTACKS"
               << "GET INVOLVED WITH STREAMING"
               <<"HOW TO SIGNUP"
              <<"FILTERS"
              <<"STREAMING DOS AND DON'T"
             <<"BUILDING AN AUDIENCE"
            << "BE AWESOME"
            << "MAKING FRIENDS"
            << "HAVING TROUBLE?"
            << "EVERYONE LOVES GIFTS"
            << "RUN A TOURNAMENT";

    CustomWidget *streamingToolWid = new CustomWidget("Streaming",QString(), szStreamingMenuList, m_parentFrame);
    connect(streamingToolWid,SIGNAL(sigDisplayPopUp(QString)), this, SLOT(slotDisplayPopUp(QString)));
    headertoolBar->addWidget(streamingToolWid);

    QStringList szGamersMenuList;
    szGamersMenuList << "GAME TESTER COMMUNITY"
                     << "SUBMIT YOUR CLASH ROYALE DECK";

    CustomWidget *gamerToolWid = new CustomWidget("Gamers",QString(), szGamersMenuList, m_parentFrame);
    connect(gamerToolWid,SIGNAL(sigDisplayPopUp(QString)), this, SLOT(slotDisplayPopUp(QString)));
    headertoolBar->addWidget(gamerToolWid);

    QStringList szAboutMenuList;
    szAboutMenuList << "ABOUT US"
                     << "APP PLAYER"
                     << "UPDATE NOTES"
                     << "FEATURES"
                     << "INVESTORS"
                     <<"PRESS"
                    << "CAREERS"
                    << "PARTNERS"
                    << "PRESS KIT"
                    << "TEAM";

    CustomWidget *aboutToolWid = new CustomWidget("About",QString(), szAboutMenuList, m_parentFrame);
    connect(aboutToolWid,SIGNAL(sigDisplayPopUp(QString)), this, SLOT(slotDisplayPopUp(QString)));
    headertoolBar->addWidget(aboutToolWid);

    CustomWidget *blogToolWid = new CustomWidget("Blog","You can discover tons of information in our blogs.",QStringList(), m_parentFrame);
    connect(blogToolWid, SIGNAL(sigDisplayPopUp(QString)), this, SLOT(slotDisplayPopUp(QString)));
    headertoolBar->addWidget(blogToolWid);

    CustomWidget *supportToolWid = new CustomWidget("Support",
                                                 "We are here to help you. Just SHOOT",
                                                 QStringList(),
                                                 m_parentFrame);
    connect(supportToolWid, SIGNAL(sigDisplayPopUp(QString)), this, SLOT(slotDisplayPopUp(QString)));
    headertoolBar->addWidget(supportToolWid);

    CustomWidget *contactToolWid = new CustomWidget("Contact Us","Its secret",QStringList(), m_parentFrame);
    connect(contactToolWid, SIGNAL(sigDisplayPopUp(QString)), this, SLOT(slotDisplayPopUp(QString)));
    headertoolBar->addWidget(contactToolWid);

    CustomWidget *enterPriseWid = new CustomWidget("Enterprise",
                                                 "You seem to be a important customer. Let me present the best from us.",
                                                 QStringList(),
                                                 m_parentFrame);
    connect(enterPriseWid, SIGNAL(sigDisplayPopUp(QString)), this, SLOT(slotDisplayPopUp(QString)));
    headertoolBar->addWidget(enterPriseWid);

    QWidget *spacer = new QWidget(m_parentFrame);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacer->setStyleSheet("background-color:transparent;");
    headertoolBar->addWidget(spacer);

    parseXMLFile();

    m_countryCBox = new QComboBox(this);
    m_countryCBox->setStyleSheet("QComboBox{background-color:transparent; color:white;border : 2px solid #FFFFFF;combobox-popup: 0;border-radius:4px; }"\
                               "QComboBox::drop-down {border: 0px;}"\
                               " QComboBox::down-arrow {image: url(:/resources/white-arrow-down.png); width: 25px; height: 25px;}"\
                               "QComboBox QAbstractItemView { border: 1px solid white; selection-background-color: transparent;background-color: transparent; color:white; width:10px;}");
    m_countryCBox->setView(new QListView);
    m_countryCBox->setStyle(new QProxyStyle);
    m_countryCBox->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_countryCBox->view()->setMinimumHeight(350);
    m_countryCBox->setContentsMargins(0,10,20,10);
    m_countryCBox->setFont(menuFont);
    m_countryCBox->setCursor(Qt::PointingHandCursor);
    updateCountryComboBox();

    headertoolBar->addWidget(m_countryCBox);
    menuHBoxLayout->addWidget(headertoolBar);
    vBoxLayout->addLayout(menuHBoxLayout);

    QWidget *hdrLblMainWid = new QWidget(m_parentFrame);
    hdrLblMainWid->setStyleSheet("background-color:transparent;");
    QGridLayout *descGLayout = new QGridLayout(this);
    descGLayout->setContentsMargins(0,0,50,0);

    QLabel *headingLbl = new QLabel(m_parentFrame);
    headingLbl->setText("BlueStacks Editor's Choice");
    headingLbl->setStyleSheet("color: #53A7E6; background-color:transparent;");
    headingLbl->setFont(QFont("Times",14));
    headingLbl->setContentsMargins(50,12,0,12);
    descGLayout->addWidget(headingLbl,0,0,1,1);

    QLabel *headingDescLbl = new QLabel(m_parentFrame);
    headingDescLbl->setText("Every week we pick our favorite Android apps that look and play beautifully on your PC.");
    headingDescLbl->setStyleSheet("color: white; background-color:transparent;");
    headingDescLbl->setFont(QFont("Times",11));
    headingDescLbl->setContentsMargins(50,12,0,12);
    descGLayout->addWidget(headingDescLbl,1,0,1,1);

    QPushButton *headingPBtn = new QPushButton(m_parentFrame);
    headingPBtn->setText("Download BlueStacks");
    headingPBtn->setStyleSheet("QPushButton{color: white; background-color:#81D3EC; border-radius:5px; padding: 1px;}"\
                               "QPushButton:hover {background-color: #65A5B9;}");
    headingPBtn->setFont(QFont("Times",11, QFont::Bold));
    headingPBtn->setContentsMargins(0,0,50,0);
    QFontMetrics displayNameFontMetrics(headingPBtn->font());
    QRect boundingRect = displayNameFontMetrics.boundingRect(headingPBtn->text());
    int width = boundingRect.width();

    headingPBtn->setMinimumWidth(width);
    headingPBtn->setMinimumHeight(40);
    headingPBtn->setCursor(Qt::PointingHandCursor);
    descGLayout->addWidget(headingPBtn,0,1,2,1, Qt::AlignRight);

    hdrLblMainWid->setLayout(descGLayout);

    vBoxLayout->addWidget(hdrLblMainWid);

    QHBoxLayout * sliderSpaceWidHBoxLayout = new QHBoxLayout(m_parentFrame);
    SlideShow *sliderMainWid = new SlideShow(m_parentFrame);
    sliderMainWid->startShow();
    sliderMainWid->show();
    connect(sliderMainWid, SIGNAL(sigImageChanged(QString)), this, SLOT(slotSetBackgroundImage(QString)));

    sliderSpaceWidHBoxLayout->addWidget(sliderMainWid);
    sliderSpaceWidHBoxLayout->setContentsMargins(50,0,50,10);

    vBoxLayout->addLayout(sliderSpaceWidHBoxLayout);

    parentLayout->addWidget(m_parentFrame);
    this->setLayout(parentLayout);

    this->setWindowTitle("BlueStacks");
}

void MainWidget::parseXMLFile()
{
    QFile *xmlFile = new QFile(":/XML/countries.xml");
    if (nullptr != xmlFile) {
        if (xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QXmlStreamReader xmlStreamReader(xmlFile);
            while(!xmlStreamReader.hasError() && !xmlStreamReader.atEnd())
            {
                // Read next element
                QXmlStreamReader::TokenType tokenType = xmlStreamReader.readNext();

                //If token type is just start document then go for next
                if ( tokenType == QXmlStreamReader::StartDocument)
                    continue;
                // If token type is start element then read it
                if ( tokenType == QXmlStreamReader::StartElement )
                {
                    if (xmlStreamReader.name() == QStringLiteral("countries"))
                        continue;
                    if (xmlStreamReader.name() == QStringLiteral("country"))
                        parseCountry(xmlStreamReader);
                }
            }
        }
    }
}

void MainWidget::parseCountry(QXmlStreamReader &xml)
{
    QMap<QString, QString> countryCodeNameMap;

    QXmlStreamAttributes attributes = xml.attributes();

    if (attributes.hasAttribute("code") && attributes.hasAttribute("iso"))
    {
        xml.readNext();
        countryCodeNameMap[attributes.value("code").toString()] = xml.text().toString();
    }

    QMapIterator<QString, QString> mapIter(countryCodeNameMap);
    while(mapIter.hasNext()) {
        mapIter.next();
        m_countryMap.insert(mapIter.key(),mapIter.value());
    }
}

void MainWidget::updateCountryComboBox()
{
    if ( m_countryCBox ) {
        m_countryCBox->clear();

        QDir dir(":/Countries");
        QStringList fileNames = dir.entryList(QDir::Files | QDir::Readable, QDir::Name);
        for (int nIndex1=0; nIndex1<fileNames.count(); nIndex1++) {
            m_countryCBox->addItem(QIcon(QString(":/Countries/"+fileNames[nIndex1])), m_countryMap[fileNames[nIndex1].section(".",0,0).toUpper()]);
            if( fileNames[nIndex1].contains("US", Qt::CaseInsensitive)) {
                m_countryCBox->setCurrentIndex(nIndex1);
            }
        }
    }
}

void MainWidget::slotDisplayPopUp(QString szMsg)
{
    QMessageBox msgBox(QMessageBox::Information, "BlueStacks",szMsg, QMessageBox::Ok, this);
    msgBox.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
    msgBox.exec();
}
