#ifndef ATTITUDEINDICATOR_H
#define ATTITUDEINDICATOR_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QtMath>

namespace Ui {
class AttitudeIndicator;
}

class AttitudeIndicator : public QWidget
{
    Q_OBJECT

public:
    explicit AttitudeIndicator(QWidget *parent = nullptr);
    ~AttitudeIndicator();

    void updateAttitude(qreal pitch, qreal roll);

private:
    Ui::AttitudeIndicator *ui;
    QGraphicsSvgItem* svgItem;
    QGraphicsItemGroup* rotateGroup;  // 新增，用于绕点旋转
    QPointF  svgOriginalPos;  // 初始位置，用于俯仰偏移
};

#endif // ATTITUDEINDICATOR_H
