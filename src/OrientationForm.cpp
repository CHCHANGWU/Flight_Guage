#include "OrientationForm.h"
#include "ui_OrientationForm.h"

OrientationForm::OrientationForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OrientationForm)
{
    ui->setupUi(this);
}

OrientationForm::~OrientationForm()
{
    delete ui;
}

void OrientationForm::setCpmpassAngle(qreal angle)
{
    ui->Compass->setAngle(angle);
}

void OrientationForm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);



    drawBackground(painter);
}

void OrientationForm::drawBackground(QPainter &painter)
{
    // 1️⃣ 绘制白色边框：左、上、右
    QPen whitePen(Qt::white);
    whitePen.setWidth(5);
    painter.setPen(whitePen);
    painter.setBrush(Qt::NoBrush);

    int w = width();
    int h = height();

    // 左边线
    painter.drawLine(QPoint(0, 0), QPoint(0, h));
    // 上边线
    painter.drawLine(QPoint(0, 0), QPoint(w, 0));

    painter.drawLine(QPoint(0, h), QPoint(w, h));

    // 设置填充颜色为浅蓝色
    QBrush brush(QColor("#19d0ed")); // 浅蓝色 RGB
    painter.setBrush(brush);

    // 设置轮廓颜色为白色
    QPen pen(Qt::white);
    pen.setWidth(2); // 可选，设置轮廓宽度
    painter.setPen(pen);

    // 定义三角形的三个点
    QPoint p1(40, 6);
    QPoint p2(20, 30);
    QPoint p3(60, 30);
    QPoint p4(600, 30);
    QPoint p5(580, 6);
    QPoint p6(620, 6);

    QPolygon leftTriangle;
    leftTriangle << p1 << p2 << p3;

    QPolygon rightTriangle;
    rightTriangle << p4 << p5 << p6;

    // 绘制三角形
    painter.drawPolygon(leftTriangle);
    painter.drawPolygon(rightTriangle);
}
