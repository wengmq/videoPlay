#ifndef CONTENTBOTTOMWIDGETTITLEBAR_H
#define CONTENTBOTTOMWIDGETTITLEBAR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
const QString main_style4 = "QFrame{background:rgb(255,250,250);}";

#pragma pack(push)
#pragma pack(1)

class ContentBottomWidgetTitleBar: public QFrame
{
    Q_OBJECT
public:
    explicit ContentBottomWidgetTitleBar(QWidget *parent =0);
    ~ContentBottomWidgetTitleBar(){}

    QPushButton *recommendBtn;
    QPushButton *libBtn;



private:
    void TitleInit();
    QHBoxLayout *titleLayout;
};

#pragma pack(pop)
#endif // CONTENTBOTTOMWIDGETTITLEBAR_H
