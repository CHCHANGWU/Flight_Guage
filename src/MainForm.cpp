#include "MainForm.h"
#include "ui_MainForm.h"
#include <QTimer>
#include <QDebug>

MainForm::MainForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);

    init();
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::init()
{
    setWindowFlag(Qt::FramelessWindowHint);
    // ✅ 不设置 parent
    timerWork = new TimerWorker();

    m_TimerWorkerThread = new QThread(this);

    // ✅ 正确地移动 TimerWorker 到子线程
    timerWork->moveToThread(m_TimerWorkerThread);

    // ✅ 定时器线程向 UI 发信号，UI 在主线程更新
    connect(timerWork, &TimerWorker::sig_SetLeftEnginePower, ui->ststusWidget, &StatusForm::setLeftEnginePower);
    connect(timerWork, &TimerWorker::sig_SetRightEnginePower, ui->ststusWidget, &StatusForm::setrightEnginePower);
    connect(timerWork, &TimerWorker::sig_SetAttitudeIndicatorPos, ui->gyroFrom, &GyroForm::setAttitudeIndicatorPos);
    connect(timerWork, &TimerWorker::sig_SetAzimuthAngle, ui->gyroFrom, &GyroForm::setAzimuthAngle);
    connect(timerWork, &TimerWorker::sig_SetCpmpassAngle, ui->orientation, &OrientationForm::setCpmpassAngle);

    // ✅ 线程启动后开始逻辑
    connect(m_TimerWorkerThread, &QThread::started, timerWork, &TimerWorker::start);

    // ✅ 线程退出时清理资源
    connect(m_TimerWorkerThread, &QThread::finished, timerWork, &QObject::deleteLater);
    connect(this, &MainForm::destroyed, m_TimerWorkerThread, &QThread::quit);
    connect(m_TimerWorkerThread, &QThread::finished, m_TimerWorkerThread, &QObject::deleteLater);

    // 启动线程
    m_TimerWorkerThread->start();
}
