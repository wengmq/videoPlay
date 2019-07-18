#include <QMenu>
#include <QFile>

#include "TitleBar.h"

TitleBar::TitleBar(QWidget *parent) : QFrame(parent)
{
    setMouseTracking(true);
    initTitle();
}

void TitleBar::initTitle()
{
    setStyleSheet(::main_style);

    setMinimumSize(1000,45);
    setMaximumSize(1920,45);

    titleLayout = new QHBoxLayout(this);

    titleIconBtn = new QPushButton;
    titleIconBtn->setIcon(QIcon("../image/btn/title/QIYLogo.jpg"));
    titleIconBtn->setIconSize(QSize(100,45));
    titleIconBtn->setFlat(true);
    titleIconBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
    titleIconBtn->adjustSize();
    titleIconBtn->setCursor(Qt::PointingHandCursor);

    //for trigon list
    QMenu *loginMenu = new QMenu;

    titleIconBtn->setMenu(loginMenu);




    LayoutLeft = new QHBoxLayout;

//    videoBtn = new QPushButton;
//    videoBtn->setIcon(QIcon("../image/btn/title/video1.jpg"));
//    videoBtn->setIconSize(QSize(70,36));
//    videoBtn->setFlat(true);
//    videoBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
//    videoBtn->setDisabled(true);
//    videoBtn->setCursor(Qt::PointingHandCursor);

//    findBtn = new QPushButton;
//    findBtn->setIcon(QIcon("../image/btn/title/find1.jpg"));
//    findBtn->setIconSize(QSize(70,36));
//    findBtn->setFlat(true);
//    findBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
//    //findBtn->setDisabled(true);
//    findBtn->setCursor(Qt::PointingHandCursor);

//    paopaoBtn = new QPushButton;
//    paopaoBtn->setIcon(QIcon("../image/btn/title/paopao1.jpg"));
//    paopaoBtn->setIconSize(QSize(70,36));
//    paopaoBtn->setFlat(true);
//    paopaoBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
//    //paopaoBtn->setDisabled(true);
//    paopaoBtn->setCursor(Qt::PointingHandCursor);

    searchEdit = new QLineEdit;
    //searchEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    searchEdit->setFixedSize(400,30);
    searchEdit->setPlaceholderText("搜索电视剧、电影...");

    searchBtn = new QPushButton(searchEdit);
    searchBtn->setIcon(QIcon("../image/btn/title/search.png"));
    searchBtn->setIconSize(QSize(13,12));
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");

    QMargins margins = searchEdit->textMargins();
    searchEdit->setTextMargins(margins.left()+10, margins.top(), searchBtn->width()+15, margins.bottom());

    searchLayout = new QHBoxLayout(searchEdit);
    searchLayout->addStretch();
    searchLayout->addWidget(searchBtn);
    searchLayout->setSpacing(0);
    //btn at right
    searchLayout->setContentsMargins(0,0,3,0);

//    LayoutLeft->addWidget(videoBtn);
//    LayoutLeft->addWidget(findBtn);
//    LayoutLeft->addWidget(paopaoBtn);
//    LayoutLeft->addSpacing(40);
    LayoutLeft->addWidget(searchEdit);
//    LayoutLeft->setSpacing(0);

    LayoutRight = new QHBoxLayout;

    loginBtn = new QPushButton;
    loginBtn->setFlat(true);
    loginBtn->setCursor(Qt::PointingHandCursor);
    loginBtn->setFixedSize(60,36);
    loginBtn->setText("未登录");
//    loginBtn->setIcon(QIcon("../image/btn/title/login_t.jpg"));
//    loginBtn->setIconSize(QSize(42,36));
//   loginBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");


//    vipBtn = new QPushButton;
//    vipBtn->setFlat(true);
//    vipBtn->setCursor(Qt::PointingHandCursor);
//    vipBtn->setFixedSize(56,36);
//    vipBtn->setIcon(QIcon("../image/btn/title/VIP.jpg"));
//    vipBtn->setIconSize(QSize(56,36));
//    vipBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");

//    nullLabel = new QLabel;
//    nullLabel->setPixmap(QPixmap(":../image/btn/title/line.jpg"));


//    ideaBtn = new QPushButton;
//    ideaBtn->setCursor(Qt::PointingHandCursor);
//    ideaBtn->setFixedSize(36,36);
//    ideaBtn->setIcon(QIcon("../image/btn/title/idea.jpg"));
//    ideaBtn->setIconSize(QSize(36,36));
//    ideaBtn->setFlat(true);
//    ideaBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");

//    skinBtn = new QPushButton;
//    skinBtn->setCursor(Qt::PointingHandCursor);
//    skinBtn->setFixedSize(36,36);
//    skinBtn->setIcon(QIcon("../image/btn/title/skin.jpg"));
//    skinBtn->setIconSize(QSize(36,36));
//    skinBtn->setFlat(true);
//    skinBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");


    minimumBtn = new QPushButton;
    minimumBtn->setCursor(Qt::PointingHandCursor);
    minimumBtn->setFixedSize(36,36);
    minimumBtn->setToolTip("最小化");
    minimumBtn->setIcon(QIcon("../image/btn/title/min.jpg"));
    minimumBtn->setIconSize(QSize(36,36));
    minimumBtn->setFlat(true);
    minimumBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");


//    maximumBtn = new QPushButton;
//    maximumBtn->setCursor(Qt::PointingHandCursor);
//    maximumBtn->setFixedSize(36,36);
//    maximumBtn->setToolTip("最大化");
//    maximumBtn->setIcon(QIcon("../image/btn/title/max.jpg"));
//    maximumBtn->setIconSize(QSize(36,36));
//    maximumBtn->setFlat(true);
//    maximumBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");



    closeBtn = new QPushButton;
    closeBtn->setCursor(Qt::PointingHandCursor);
    closeBtn->setFixedSize(36,36);
    closeBtn->setToolTip("关闭");
    closeBtn->setIcon(QIcon("../image/btn/title/close.jpg"));
    closeBtn->setIconSize(QSize(36,36));
    closeBtn->setFlat(true);
    closeBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");

    LayoutRight->setSpacing(5);
    LayoutRight->addWidget(loginBtn);
    LayoutRight->addSpacing(50);
//    LayoutRight->addWidget(vipBtn);
//    LayoutRight->addSpacing(2);
//    LayoutRight->addWidget(nullLabel);
//    LayoutRight->addSpacing(2);
//    LayoutRight->addWidget(ideaBtn);
//    LayoutRight->addSpacing(0);
//    LayoutRight->addWidget(skinBtn);
//    LayoutRight->addSpacing(0);
    LayoutRight->addWidget(minimumBtn);
//    LayoutRight->addSpacing(5);
//    LayoutRight->addWidget(maximumBtn);
    LayoutRight->addSpacing(5);
    LayoutRight->addWidget(closeBtn);

    titleLayout->addWidget(titleIconBtn);
    titleLayout->addSpacing(150);
    titleLayout->addLayout(LayoutLeft);
    titleLayout->addStretch();
    titleLayout->addLayout(LayoutRight);
}

