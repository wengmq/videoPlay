#ifndef CW_VIDEOWIDGETUPPER_H
#define CW_VIDEOWIDGETUPPER_H

#include <QFrame>
#include <QVector>
#include <QLabel>
#include <QToolBar>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QIcon>
#include <QAction>
#include <QTimer>
const int image_count = 6;
const int center_width = 600;
const int center_hieght =  230;
const int margin_height = 200;

const QString main_style2 = "QFrame{background:rgb(248,248,255);}";

#pragma pack(push)
#pragma pack(1)

class CW_VideoWidgetUpper: public QFrame
{
    Q_OBJECT
public:
    explicit CW_VideoWidgetUpper(QWidget *parent =0);
    ~CW_VideoWidgetUpper(){}


    void actionTimerStart();
//    QPushButton *leftBtn;
//    QPushButton *rightBtn;
//    QPushButton *middleBtn;

//    QPushButton *typeBtn1;
//    QPushButton *typeBtn2;
//    QPushButton *typeBtn3;
//    QPushButton *typeBtn4;
//    QPushButton *typeBtn5;
//    QPushButton *typeBtn6;
//    QPushButton *typeBtn7;
//    QPushButton *typeBtn8;
//    QPushButton *typeBtn9;

private:
    int margin_width;
    int default_choose;

protected slots:
    void onHoverAction();

private:
    void moveLeft();
    void moveRight();

    QRect center_rect;
    QRect left_rect;
    QRect right_rect;

    QLabel *center_label;
    QLabel *left_label;
    QLabel *right_label;

    QPropertyAnimation *moveAnimation;
    QPropertyAnimation *moveAnimation_left;
    QPropertyAnimation *moveAnimation_right;

    QToolBar *transferBar;
    QVector<QPixmap> label_group;
    QAction *lineAction[image_count];

    QTimer *actionTime;

    void resizeEvent(QResizeEvent*);

//    QHBoxLayout *totalLayout;
//    QHBoxLayout *leftLayout;

//    QVBoxLayout *rightLayout;
//    QHBoxLayout *LayoutRight1;
//    QHBoxLayout *LayoutRight2;
//    QHBoxLayout *LayoutRight3;
//    QHBoxLayout *LayoutRight4;
//    QHBoxLayout *LayoutRight5;

//    void UiInit();
};

#pragma pack(pop)
#endif // CW_VIDEOWIDGETUPPER_H
