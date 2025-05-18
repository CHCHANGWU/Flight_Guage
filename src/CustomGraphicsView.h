#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

class CustomGraphicsView : public QGraphicsView
{
public:
    enum E_CLASSTYPE
    {
        E_CLASSTYPE_ATT,
        E_CLASSTYPE_AOMMPASS,
    };
    using QGraphicsView::QGraphicsView;
    CustomGraphicsView(QWidget* parent = nullptr);

    void setCurrentType(E_CLASSTYPE type);

protected:
    void drawForeground(QPainter *painter, const QRectF &rect) override;

private:
    E_CLASSTYPE  m_CurrentType = E_CLASSTYPE_ATT;
};

#endif // CUSTOMGRAPHICSVIEW_H
