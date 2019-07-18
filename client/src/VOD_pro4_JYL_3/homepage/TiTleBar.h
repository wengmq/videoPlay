#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

const QString main_style = "QFrame{background:rgb(255,255,255);}";

#pragma pack(push)
#pragma pack(1)

class TitleBar : public QFrame
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent =0);
    ~TitleBar(){}

    QPushButton *titleIconBtn;
    QLabel *nullLabel;

//    QPushButton *videoBtn;
//    QPushButton *findBtn;
//    QPushButton *paopaoBtn;
    QPushButton *searchBtn;
    QLineEdit *searchEdit;

    QPushButton *loginBtn;
//    QPushButton *vipBtn;
//    QPushButton *ideaBtn;
//    QPushButton *skinBtn;
    QPushButton *minimumBtn;
   // QPushButton *maximumBtn;
    QPushButton *closeBtn;


private:
    void initTitle();

    QHBoxLayout *titleLayout;
    QHBoxLayout *searchLayout;
    QHBoxLayout *LayoutLeft;
    QHBoxLayout *LayoutRight;


};

#pragma pack(pop)

#endif // TITLEBAR_H
