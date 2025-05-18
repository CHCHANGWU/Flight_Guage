#ifndef COMPASSWIDGET_H
#define COMPASSWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QtMath>

namespace Ui {
class CompassWidget;
}

class CompassWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CompassWidget(QWidget *parent = nullptr);
    ~CompassWidget();

    void setAngle(qreal angle);

private:
    Ui::CompassWidget *ui;
    QGraphicsSvgItem* svgItem;
    QGraphicsItemGroup* rotateGroup;  // 新增，用于绕点旋转
    QPointF  svgOriginalPos;  // 初始位置，用于俯仰偏移
};

#endif // COMPASSWIDGET_H
