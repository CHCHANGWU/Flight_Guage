#include "TimerWorker.h"

TimerWorker::TimerWorker(QObject *parent)
    : QObject(parent)
{
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);
}

void TimerWorker::start()
{
    connect(timer1, &QTimer::timeout, this, [=]() {
        emit sig_SetLeftEnginePower(i);
        emit sig_SetRightEnginePower(i);
        i += sum;
        if(i > 295.0) sum = -0.1;
        if(i < 0.1) sum = 0.1;
        emit sig_SetCpmpassAngle(angle);
        angle += angleSum;
        emit sig_SetAzimuthAngle(angle);
        if(angle > 359.9) angle = 0;
    });
    timer1->start(1000);

    // connect(timer2, &QTimer::timeout, this, [=]() {
    //     if(index == m_FilightData.size()) {
    //         timer2->stop();
    //         return;
    //     }
    //     emit sig_SetAttitudeIndicatorPos(m_FilightData[index].first, m_FilightData[index].second);
    //     index++;
    // });
    // timer2->start(100);

    // connect(timer3, &QTimer::timeout, this, [=]() {
    //     emit sig_SetCpmpassAngle(angle);
    //     angle += angleSum;
    //     emit sig_SetAzimuthAngle(angle);
    //     if(angle > 359.9) angle = 0;
    // });
    // timer3->start(1);
}
