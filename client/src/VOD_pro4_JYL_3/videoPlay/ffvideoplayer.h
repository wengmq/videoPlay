#ifndef FFVIDEOPLAYER_H
#define FFVIDEOPLAYER_H

#include <QDialog>
#include <QFileDialog>
#include <QList>
#include <QMouseEvent>
#include "m_ffmpeg.h"
#include "m_audio.h"
#include "m_thread.h"
#include <Qlabel>
namespace Ui {
class FFVideoPlayer;
}

class FFVideoPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit FFVideoPlayer(QWidget *parent = 0);
    ~FFVideoPlayer();
    void timerEvent(QTimerEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void on_open_Btn_released(QString url);

public slots:


    void on_play_Btn_released();

    void on_timeSlider_sliderPressed();

    void on_timeSlider_sliderReleased();

    void dialogCloseSlot();

private:
    Ui::FFVideoPlayer *ui;
    m_FFmpeg *FFmpeg;
    m_Thread *rtsp;


};

#endif // FFVIDEOPLAYER_H

