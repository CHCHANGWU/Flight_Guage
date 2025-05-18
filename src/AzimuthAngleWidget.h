#ifndef AZIMUTHANGLEWIDGET_H
#define AZIMUTHANGLEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <cmath>

namespace Ui {
class AzimuthAngleWidget;
}

class AzimuthAngleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AzimuthAngleWidget(QWidget *parent = nullptr);
    ~AzimuthAngleWidget();

    void setAngle(qreal angle);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    Ui::AzimuthAngleWidget *ui;
    qreal m_CurrentAngle = 0;
};

#endif // AZIMUTHANGLEWIDGET_H
