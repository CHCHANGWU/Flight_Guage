#include "CompassWidget.h"
#include "ui_CompassWidget.h"

CompassWidget::CompassWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CompassWidget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    // 创建场景并设置大小（与视图一样大）
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setCurrentType(CustomGraphicsView::E_CLASSTYPE_AOMMPASS);
    // 设置 scene 大小等于 view 大小
    QSizeF viewSize = ui->graphicsView->size();
    scene->setSceneRect(0, 0, viewSize.width(), viewSize.height());

    // 创建 SVG 图元（飞机姿态背景）
    svgItem = new QGraphicsSvgItem(":/image/compass.svg");
    svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
    svgItem->setCacheMode(QGraphicsItem::NoCache);

    scene->addItem(svgItem);
    // 获取 scene 的中心点
    QPointF sceneCenter = scene->sceneRect().center();

    // 获取 svgItem 的边界尺寸
    QRectF svgBounds = svgItem->boundingRect();

    // 设置 svgItem 的位置，使其中心对齐 scene 中心
    QPointF centerPos = sceneCenter - QPointF(svgBounds.width() / 2.0, svgBounds.height() / 2.0 - 300);
    svgItem->setPos(centerPos);

    // 缩放视图
    ui->graphicsView->scale(0.8, 0.8);
    ui->graphicsView->setStyleSheet("border: none; background: transparent;");

}

CompassWidget::~CompassWidget()
{
    delete ui;
}

void CompassWidget::setAngle(qreal angle)
{
    if (!svgItem)
        return;

    // 设置旋转中心为 SVG 图元的中心
    QRectF bounds = svgItem->boundingRect();
    svgItem->setTransformOriginPoint(bounds.center());

    // 设置旋转角度（单位为度，正数为顺时针）
    svgItem->setRotation(-angle);
}
