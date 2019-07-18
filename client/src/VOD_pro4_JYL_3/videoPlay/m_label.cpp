#include "m_label.h"

m_Label::m_Label(QWidget *parent) :
    QLabel(parent)
{

    startTimer(5);
    m_Thread::getObj()->start();
}

m_Label::~m_Label()
{
}

void m_Label::paintEvent(QPaintEvent *e)
{
    static QImage *image = NULL;

    static int w = 0; //��¼֮ǰ�Ĵ��ڴ�С
    static int h = 0;
    if (w != this->width() || h != this->height())
    {
        //������ڴ�С�����仯��ɾ���ڴ�
        if (image)
        {
            delete image->bits();  //ɾ��QImage���ڲ��ռ�
            delete image;
            image = NULL;
        }
    }

    if (image == NULL)
    {
        uchar *buf = new uchar[this->width() * this->height() * 4];
        image = new QImage(buf, this->width(), this->height(), QImage::Format_ARGB32);
    }

    m_FFmpeg::getObj()->YuvToRGB((char *)(image->bits()), this->width(), this->height());

    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0, 0), *image);
    painter.end();
}

void m_Label::timerEvent(QTimerEvent *e)
{
    this->update();
}
