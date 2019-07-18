#include "CW_VideoWidgetUpper.h"

CW_VideoWidgetUpper::CW_VideoWidgetUpper(QWidget *parent): QFrame(parent)
{
//    setMouseTracking(true);
//    UiInit();
    actionTime = new QTimer();
    setStyleSheet(::main_style2);
     margin_width = 110;
     default_choose = 0;
    for(int i=1;i<image_count+1;i++)
        {
            QPixmap temp_label = QPixmap("../image/btn/video/"+QString::number(i)+".jpg");
            label_group.push_back(temp_label);
        }

        int width = this->width();
        int height = this->height();

        int pos_center_xstart =(width-center_width)/2;
        int pos_center_ystart=(height-center_hieght)/2;
        center_rect.setRect(pos_center_xstart,pos_center_ystart,center_width,center_hieght);
        center_label = new QLabel(this);
        center_label->setPixmap(label_group[0]);
        center_label->setGeometry(pos_center_xstart,pos_center_ystart,center_width,center_hieght);

        int pos_left_xstart = pos_center_xstart - margin_width;
        int pos_left_ystart = pos_center_ystart + center_hieght - margin_height;
        left_rect.setRect(pos_left_xstart,pos_left_ystart,margin_width,margin_height);
        left_label =new QLabel(this);
        left_label->setPixmap(label_group[5]);
        left_label->setGeometry(pos_left_xstart,pos_left_ystart,margin_width,margin_height);

        int pos_right_xstart = pos_center_xstart + center_width;
        int pos_right_ystart = pos_center_ystart + center_hieght - margin_height;
        right_rect.setRect(pos_right_xstart,pos_right_ystart,margin_width,margin_height);
        right_label =new QLabel(this);
        right_label->setPixmap(label_group[1]);
        right_label->setGeometry(pos_right_xstart,pos_right_ystart,margin_width,margin_height);

        //line bar
        transferBar = new QToolBar(this);
        transferBar->setGeometry(pos_center_xstart+center_width/2-40,pos_center_ystart+center_hieght+10,17*image_count*2,24);
        transferBar->setStyleSheet("border:none;");
        transferBar->setIconSize(QSize(17,23));
        for(int actions_num = 0;actions_num < image_count;actions_num++)
        {
            lineAction[actions_num]=new QAction(QIcon("../image/btn/video/line.png"),"",transferBar);
            lineAction[actions_num]->setData(actions_num);
            //°ó¶¨ÂÖ²¥ÐÅºÅ²Û
            connect(lineAction[actions_num],SIGNAL(hovered()),this,SLOT(onHoverAction()));
            //connect(actionTime,SIGNAL(timeout()),this,SLOT(onHoverAction()));

            transferBar->addAction(lineAction[actions_num]);
        }
        lineAction[default_choose]->setIcon(QIcon("../image/btn/video/lineChose.png"));

        moveAnimation_left = new QPropertyAnimation(left_label,"geometry");
        moveAnimation = new QPropertyAnimation(center_label,"geometry");
        moveAnimation_right=new QPropertyAnimation(right_label,"geometry");

}
void CW_VideoWidgetUpper::actionTimerStart()
{
    actionTime->start(1000);
}

/*void CW_VideoWidgetUpper::UiInit()
{
    setStyleSheet(::main_style2);

//    setMinimumSize(1000,250);
//    setMaximumSize(1920,250);

//    totalLayout = new QHBoxLayout(this);
//    leftLayout = new QHBoxLayout;

//    leftBtn = new QPushButton;
//    leftBtn->setFixedSize(90,240);

//    middleBtn = new QPushButton;
//    middleBtn->setFixedSize(600,240);

//    rightBtn = new QPushButton;
//    rightBtn->setFixedSize(90,240);

//    leftLayout->addWidget(leftBtn);
//    leftLayout->addWidget(middleBtn);
//    leftLayout->addWidget(rightBtn);


//    rightLayout = new QVBoxLayout;

//    LayoutRight1 = new QHBoxLayout;
//    typeBtn1 = new QPushButton;
//    typeBtn1->setFixedSize(72,38);
//    typeBtn2 = new QPushButton;
//    typeBtn2->setFixedSize(72,38);
//    LayoutRight1->addWidget(typeBtn1);
//    LayoutRight1->addWidget(typeBtn2);

//    LayoutRight2 = new QHBoxLayout;
//    typeBtn3 = new QPushButton;
//    typeBtn3->setFixedSize(72,38);
//    typeBtn4 = new QPushButton;
//    typeBtn4->setFixedSize(72,38);

//    LayoutRight2->addWidget(typeBtn3);
//    LayoutRight2->addWidget(typeBtn4);

//    LayoutRight3 = new QHBoxLayout;
//    typeBtn5 = new QPushButton;
//    typeBtn5->setFixedSize(72,38);
//    typeBtn6 = new QPushButton;
//    typeBtn6->setFixedSize(72,38);

//    LayoutRight3->addWidget(typeBtn5);
//    LayoutRight3->addWidget(typeBtn6);

//    LayoutRight4 = new QHBoxLayout;
//    typeBtn7 = new QPushButton;
//    typeBtn7->setFixedSize(72,38);
//    typeBtn8 = new QPushButton;
//    typeBtn8->setFixedSize(72,38);

//    LayoutRight4->addWidget(typeBtn7);
//    LayoutRight4->addWidget(typeBtn8);

//    LayoutRight5 = new QHBoxLayout;
//    typeBtn9 = new QPushButton;
//    typeBtn9->setFixedSize(72,38);
//    LayoutRight5->addWidget(typeBtn9);

//    rightLayout->addLayout(LayoutRight1);
//    rightLayout->addLayout(LayoutRight2);
//    rightLayout->addLayout(LayoutRight3);
//    rightLayout->addLayout(LayoutRight4);
//    rightLayout->addLayout(LayoutRight5);

//    totalLayout->addLayout(leftLayout);
//    totalLayout->addLayout(rightLayout);
}
*/
// a small bug; rect mess
void CW_VideoWidgetUpper::resizeEvent(QResizeEvent* event)
{

    int width = this->width();
    int height = this->height();

    int changesize = event->size().width() - event->oldSize().width();

    margin_width = margin_width + static_cast<int>(changesize * 0.15);
    if(margin_width > 600)
        margin_width = 590;
    else if(margin_width < 110)
        margin_width = 100;

    int pos_center_xstart =(width-center_width)/2;
    int pos_center_ystart=(height-center_hieght)/2;
    center_rect.setRect(pos_center_xstart,pos_center_ystart,center_width,center_hieght);
    center_label->setGeometry(pos_center_xstart,pos_center_ystart,center_width,center_hieght);

    transferBar->setGeometry(pos_center_xstart+center_width/2-40,pos_center_ystart+center_hieght+10,17*image_count*2,24);

    int pos_left_xstart = pos_center_xstart - margin_width;
    int pos_left_ystart = pos_center_ystart + center_hieght - margin_height;
    left_rect.setRect(pos_left_xstart,pos_left_ystart,margin_width,margin_height);
    left_label->setGeometry(pos_left_xstart,pos_left_ystart,margin_width,margin_height);

    int pos_right_xstart = pos_center_xstart + center_width;
    int pos_right_ystart = pos_center_ystart + center_hieght - margin_height;
    right_rect.setRect(pos_right_xstart,pos_right_ystart,margin_width,margin_height);
    right_label->setGeometry(pos_right_xstart,pos_right_ystart,margin_width,margin_height);

    center_label->raise();

}

void CW_VideoWidgetUpper::onHoverAction()
{
    int hover_action_num = 0;
    QAction *actionSender = reinterpret_cast<QAction *>(sender());
    for(int action_num = 0; action_num < image_count; action_num++)
    {
        if(lineAction[action_num] != actionSender)
            lineAction[action_num]->setIcon(QIcon("../image/btn/video/line.png"));
        else
            hover_action_num = action_num;
    }
    actionSender->setIcon(QIcon("../image/btn/video/lineChose.png"));
    transferBar->setCursor(QCursor(Qt::PointingHandCursor));

    if(hover_action_num > default_choose)
    {
        moveLeft();
        default_choose = hover_action_num;
        center_label->setPixmap(label_group[hover_action_num == 0 ? 5 : hover_action_num - 1]);
        right_label->setPixmap(label_group[hover_action_num]);
        left_label->setPixmap(label_group[hover_action_num == 5 ? 0 : hover_action_num + 1]);
    }
    else if(hover_action_num < default_choose)
    {
        moveRight();
        default_choose = hover_action_num;
        right_label->setPixmap(label_group[hover_action_num == 0 ? 5 : hover_action_num - 1]);
        left_label->setPixmap(label_group[hover_action_num]);
        center_label->setPixmap(label_group[hover_action_num == 5 ? 0 : hover_action_num + 1]);
    }

}

void CW_VideoWidgetUpper::moveRight()
{
    moveAnimation_left->setDuration(200);
    moveAnimation_left->setStartValue(left_rect);
    moveAnimation_left->setEndValue(center_rect);
    moveAnimation_left->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation_left->start();

    moveAnimation->setDuration(200);
    moveAnimation->setStartValue(center_rect);
    moveAnimation->setEndValue(right_rect);
    moveAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation->start();

    moveAnimation_right->setDuration(200);
    moveAnimation_right->setStartValue(right_rect);
    moveAnimation_right->setEndValue(left_rect);
    moveAnimation_right->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation_right->start();

}

void CW_VideoWidgetUpper::moveLeft()
{
    moveAnimation_left->setDuration(200);
    moveAnimation_left->setStartValue(left_rect);
    moveAnimation_left->setEndValue(right_rect);
    moveAnimation_left->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation_left->start();

    moveAnimation->setDuration(200);
    moveAnimation->setStartValue(center_rect);
    moveAnimation->setEndValue(left_rect);
    moveAnimation->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation->start();

    moveAnimation_right->setDuration(200);
    moveAnimation_right->setStartValue(right_rect);
    moveAnimation_right->setEndValue(center_rect);
    moveAnimation_right->setEasingCurve(QEasingCurve::InOutQuart);
    moveAnimation_right->start();

}
