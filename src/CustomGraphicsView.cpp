#include "CustomGraphicsView.h"

CustomGraphicsView::CustomGraphicsView(QWidget *parent) : QGraphicsView(parent) {}

void CustomGraphicsView::setCurrentType(E_CLASSTYPE type)
{
    m_CurrentType = type;
    update();
}

void CustomGraphicsView::drawForeground(QPainter *painter, const QRectF &rect)
{
    if(m_CurrentType == E_CLASSTYPE_ATT)
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        // 切换到视图坐标（不受场景缩放/平移影响）
        painter->resetTransform();

        QPen pen(QColor("#6fff00"), 1);
        painter->setPen(pen);

        // 获取视图中心的 y 坐标（以视图自身为参考）
        int centerY = viewport()->height() / 2;
        int centerX = viewport()->width() / 2;

        // 定义三角形的三个点
        QPolygon leftTriangle;
        leftTriangle << QPoint(centerX, centerY) << QPoint(centerX - 70, centerY + 30) << QPoint(centerX, centerY + 15);
        QPolygon rightTriangle;
        rightTriangle << QPoint(centerX, centerY) << QPoint(centerX + 70, centerY + 30) << QPoint(centerX, centerY + 15);

        painter->setBrush(QColor("#6fff00"));
        painter->drawPolygon(leftTriangle);
        painter->drawPolygon(rightTriangle);


        // // 绘制固定在中间的水平线
        // painter->drawLine(0, centerY, viewport()->width(), centerY);

        // pen.setColor(Qt::red);
        // painter->setPen(pen);
        // painter->drawEllipse(centerX,centerY,4,4);



        painter->restore();
    }
    else if(m_CurrentType == E_CLASSTYPE_AOMMPASS)
    {

    }

}
