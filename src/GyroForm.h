#ifndef GYROFORM_H
#define GYROFORM_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class GyroForm;
}

class GyroForm : public QWidget
{
    Q_OBJECT

public:
    explicit GyroForm(QWidget *parent = nullptr);
    ~GyroForm();

public slots:
    void setAttitudeIndicatorPos(qreal pitch, qreal roll);

    void setAzimuthAngle(qreal angle);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void drawBackground(QPainter& painter);

private:
    Ui::GyroForm *ui;
};

#endif // GYROFORM_H
