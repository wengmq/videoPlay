#include "ContentBottomWidgetTitleBar.h"

ContentBottomWidgetTitleBar::ContentBottomWidgetTitleBar(QWidget *parent)
    : QFrame(parent)
{
    setMouseTracking(true);
    TitleInit();
}

void ContentBottomWidgetTitleBar::TitleInit()
{
    setStyleSheet(::main_style4);

    setMinimumSize(1000,40);
    setMaximumSize(1920,40);

    titleLayout = new QHBoxLayout(this);

    recommendBtn = new QPushButton;
    recommendBtn->setFixedSize(60,30);
    recommendBtn->setFlat(true);
    recommendBtn->setCursor(Qt::PointingHandCursor);
    recommendBtn->setText("ÍÆ¼ö");

    libBtn = new QPushButton;
    libBtn->setFixedSize(60,30);
    libBtn->setFlat(true);
    libBtn->setCursor(Qt::PointingHandCursor);
    libBtn->setText("Æ¬¿â");

    titleLayout->addSpacing(150);
    titleLayout->addWidget(recommendBtn);
    titleLayout->addSpacing(10);
    titleLayout->addWidget(libBtn);
    titleLayout->addStretch();

}
