#ifndef M_LABEL_H
#define M_LABEL_H

#include <QWidget>
#include <QLabel>
#include "m_ffmpeg.h"
#include "m_thread.h"
#include <QPainter>
#include <QList>
#include <QImage>

class m_Label : public QLabel
{
    Q_OBJECT
public:
    explicit m_Label(QWidget *parent = 0);
    ~m_Label();

protected:
    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);

signals:

public slots:

};

#endif // M_LABEL_H
