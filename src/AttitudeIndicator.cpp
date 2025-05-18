#include "AttitudeIndicator.h"
#include "ui_AttitudeIndicator.h"

#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QtMath>
#include <QDebug>

AttitudeIndicator::AttitudeIndicator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AttitudeIndicator)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    // 创建场景并设置大小（与视图一样大）
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 设置 scene 大小等于 view 大小
    QSizeF viewSize = ui->graphicsView->size();
    scene->setSceneRect(0, 0, viewSize.width(), viewSize.height());

    // 创建 SVG 图元（飞机姿态背景）
    svgItem = new QGraphicsSvgItem(":/image/attitude.svg");
    svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
    svgItem->setCacheMode(QGraphicsItem::NoCache);

    // 创建旋转组，将 svgItem 加入
    rotateGroup = new QGraphicsItemGroup();
    rotateGroup->addToGroup(svgItem);
    scene->addItem(rotateGroup);

    // 计算视图中心点
    QPointF viewCenter = scene->sceneRect().center();

    // 设置旋转中心为视图中心（仪表盘视觉中心）
    rotateGroup->setTransformOriginPoint(viewCenter);

    // 将 svgItem 的位置设置为使其图像中心对齐视图中心
    QRectF svgRect = svgItem->boundingRect();
    svgItem->setPos(viewCenter - svgRect.center());

    // 保存原始位置
    svgOriginalPos = svgItem->pos();

    // 缩放视图
    ui->graphicsView->scale(0.8, 0.8);
}

AttitudeIndicator::~AttitudeIndicator()
{
    delete ui;
}

/**
 * @brief AttitudeIndicator::updateAttitude
 * @param pitch 俯仰角（正：抬头，负：低头）
 * @param roll 滚转角（正负顺逆时针）
 */
void AttitudeIndicator::updateAttitude(qreal pitch, qreal roll)
{
    // 每度 pitch 对应多少像素：你可以根据需要调整
    const qreal pitchFactor = 10.0;
    if(pitch > 90) pitch = 90;
    if(pitch < -90) pitch = -90;

    // 上下移动背景图来模拟俯仰（注意是设置 Y，而不是 moveBy）
    QPointF newPos = svgOriginalPos;
    newPos.setY(svgOriginalPos.y() + pitch * pitchFactor);  // 抬头图往下移
    svgItem->setPos(newPos);

    // 绕中心点旋转仪表背景（整个 group）
    rotateGroup->setRotation(roll);
}
