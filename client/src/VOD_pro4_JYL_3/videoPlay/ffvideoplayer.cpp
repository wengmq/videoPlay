#include "ffvideoplayer.h"
#include "ui_ffvideoplayer.h"
#include "m_label.h"

//ȫ�־�̬����ֻ�ڸ�cpp�ļ�����Ч
static bool isPressSlider = false;
bool is_play = false;

FFVideoPlayer::FFVideoPlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FFVideoPlayer)
{
    ui->setupUi(this);

    startTimer(20);

    this->setWindowTitle("�����ղ�����");

    ui->curr_Time_Lab->setText("00:00:00");
    ui->curr_Time_Lab->setStyleSheet("QLabel{color:#000000}");
    ui->curr_Time_Lab->setFrameStyle(QFrame::NoFrame);

    ui->total_Time_Lab->setText("00:00:00");
    ui->total_Time_Lab->setStyleSheet("QLabel{color:#000000}");
    ui->total_Time_Lab->setFrameStyle(QFrame::NoFrame);

    //play
    ui->play_Btn->setStyleSheet("QPushButton{background-image:url(../img/b1.png)}");
    ui->play_Btn->setFlat(true);

    connect(this,SIGNAL(destroyed()),this,SLOT(dialogCloseSlot()));
}

FFVideoPlayer::~FFVideoPlayer()
{
    delete ui;
}

void FFVideoPlayer::timerEvent(QTimerEvent *e)
{
    int hou = (m_FFmpeg::getObj()->m_Pts / 1000) / 60 / 60;
    int min = (m_FFmpeg::getObj()->m_Pts / 1000) / 60;
    int sec = (m_FFmpeg::getObj()->m_Pts / 1000) % 60;
    char buf[1024] = { 0 };
    sprintf(buf, "%02d:%02d:%02d", hou, min, sec);
    ui->curr_Time_Lab->setText(buf);  //��ǰ����ʱ��

    if (m_FFmpeg::getObj()->m_Total_Ms > 0)
    {
        float rate = m_FFmpeg::getObj()->m_Pts / (float(m_FFmpeg::getObj()->m_Total_Ms));

        if (!isPressSlider)//���ɿ�ʱ����ˢ�½�����λ��
        {
            this->ui->timeSlider->setValue(rate * 100); //������λ��
        }
    }
}

void FFVideoPlayer::mousePressEvent(QMouseEvent *e)
{
    int value = ((float)(e->pos().x()) / (float)(this->width())) * (ui->timeSlider->maximum() + 1);
    ui->timeSlider->setValue(value);
}

void FFVideoPlayer::on_open_Btn_released(QString url)
{

    //replay
    qDebug() << "open url: " << url;

    int total_Ms = m_FFmpeg::getObj()->open_Video(url);//url.toLocal8Bit()

    m_Audio::getObj()->sampleRate = m_FFmpeg::getObj()->m_SampleRate;
    m_Audio::getObj()->channel = m_FFmpeg::getObj()->m_Channel;
    m_Audio::getObj()->sampleSize = 16;

    m_Audio::getObj()->start();  //������Ƶ

    char buf[1024] = { 0 };
    int hou = (total_Ms / 1000) / 60 / 60;
    int min = (total_Ms / 1000) / 60;
    int sec = (total_Ms / 1000) % 60;
    sprintf(buf, "%02d:%02d:%02d", hou, min, sec);
    this->ui->total_Time_Lab->setText(buf);

    m_FFmpeg::getObj()->m_IsPlay = true;

}

void FFVideoPlayer::on_play_Btn_released()
{

    if(is_play == false)
    {
        m_FFmpeg::getObj()->m_IsPlay = true;  //�߳����У���Ƶ����
        ui->play_Btn->setStyleSheet("QPushButton{background-image:url(../img/b1.png)}");
        is_play = true;
    }else if(is_play == true)
    {
        m_FFmpeg::getObj()->m_IsPlay = false; //�߳���������Ƶ��ͣ
        ui->play_Btn->setStyleSheet("QPushButton{background-image:url(../img/b0.png)}");
        is_play = false;
    }


}

void FFVideoPlayer::dialogCloseSlot()
{
    m_FFmpeg::getObj()->m_IsPlay = false;
}


void FFVideoPlayer::on_timeSlider_sliderPressed()
{
    m_FFmpeg::getObj()->m_IsPlay = false;
    isPressSlider = true;
}

void FFVideoPlayer::on_timeSlider_sliderReleased()
{
    isPressSlider = false;
    m_FFmpeg::getObj()->m_IsPlay = true;
    float pos = 0;
    pos = this->ui->timeSlider->value() / (float)(ui->timeSlider->maximum() + 1); //��0��ʼ�ģ������÷�ĸΪ0
    m_FFmpeg::getObj()->seek(pos);
}
