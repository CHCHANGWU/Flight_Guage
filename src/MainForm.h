#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QThread>

#include "TimerWorker.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainForm;
}
QT_END_NAMESPACE

class MainForm : public QWidget
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = nullptr);
    ~MainForm();

private:
    void init();

    void test();


private:
    Ui::MainForm *ui;

    QThread*    m_StatusWidgetThread;
    QThread*    m_GyroFromThread;
    QThread*    m_OrientationThread;
    QThread*    m_TimerWorkerThread;

    TimerWorker* timerWork;
};
#endif // MAINFORM_H
