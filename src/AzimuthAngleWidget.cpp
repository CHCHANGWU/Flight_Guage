#include "AzimuthAngleWidget.h"
#include "ui_AzimuthAngleWidget.h"

#include <QDebug>

AzimuthAngleWidget::AzimuthAngleWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AzimuthAngleWidget)
{
    ui->setupUi(this);
}

AzimuthAngleWidget::~AzimuthAngleWidget()
{
    delete ui;
}

void AzimuthAngleWidget::setAngle(qreal angle)
{
    m_CurrentAngle = angle;
    update();
}

void AzimuthAngleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::white);
    pen.setWidth(2);

    painter.setPen(pen);

    QFont font("思源黑体",16);
    painter.setFont(font);

    painter.drawLine(0, height() - 2, width(), height() - 2);

    if(qFuzzyCompare(std::fmod(m_CurrentAngle, 10.0), 0.0))
    {
        // 保存当前坐标状态
        painter.save();
        painter.translate(width() / 2, height() - 2);
        int step = 1;
        int tempAngle = m_CurrentAngle;
        for(int i = 0; i <= width(); i += 50)
        {
            if(step % 2 == 0)
            {
                painter.drawLine(i, 0, i, -10);
            }
            else
            {
                QRect textRect(i - 20, -57, 40, 50);  // 左上角 (-20,-275)，宽40高20
                int angle = (tempAngle >= 360) ? (tempAngle - 360) :  tempAngle;  // 保证是正角度
                QString text = QString::number(angle / 10);
                if(angle == 0) text = "N";
                if(angle == 90) text = "E";
                if(angle == 180) text = "S";
                if(angle == 270) text = "W";
                painter.drawText(textRect, Qt::AlignCenter, text);
                painter.drawLine(i, 0, i, -15);
            }
            tempAngle+=5;
            step++;
        }
        // ➤ 左边刻度线
        tempAngle = m_CurrentAngle;
        step = 2;
        for(int i = - 50; i >= -width(); i -= 50)
        {
            if(step % 2 == 0)
            {
                painter.drawLine(i, 0, i, -10);
            }
            else
            {
                QRect textRect(i - 20, -57, 40, 50);
                int angle = (tempAngle < 0) ? (360 + tempAngle) :  tempAngle;  // 保证是正角度
                QString text = QString::number(angle / 10);
                if(angle == 0) text = "N";
                if(angle == 90) text = "E";
                if(angle == 180) text = "S";
                if(angle == 270) text = "W";
                painter.drawText(textRect, Qt::AlignCenter, text);
                painter.drawLine(i, 0, i, -15);
            }
            step++;
            tempAngle-=5;
        }
        // 恢复到之前的坐标系统
        painter.restore();
    }
    else
    {
        // 保存当前坐标状态
        painter.save();
        painter.translate(width() / 2, height() - 2);
        int ones = (int)m_CurrentAngle % 10;
        if(ones < 5)
        {
            double diff = 5 - ones;
            double tempAngle = m_CurrentAngle + diff;
            int step = 2;
            for(int i = diff * 10; i <= width(); i += 50)
            {
                if(step % 2 == 0)
                {
                    painter.drawLine(i, 0, i, -10);
                }
                else
                {
                    QRect textRect(i - 20, -57, 40, 50);
                    int angle = (tempAngle < 0) ? (360 + tempAngle) :  tempAngle;  // 保证是正角度
                    QString text = QString::number(angle / 10);
                    if(angle == 0) text = "N";
                    if(angle == 90) text = "E";
                    if(angle == 180) text = "S";
                    if(angle == 270) text = "W";
                    painter.drawText(textRect, Qt::AlignCenter, text);
                    painter.drawLine(i, 0, i, -15);
                }
                step++;
                tempAngle+=5;
            }
            diff = ones - 0; // 2
            tempAngle = m_CurrentAngle - diff; // 0
            step = 1;
            for(int i = -diff * 10; i >= -width(); i -= 50)
            {
                if(step % 2 == 0)
                {
                    painter.drawLine(i, 0, i, -10);
                }
                else
                {
                    QRect textRect(i - 20, -57, 40, 50);
                    int angle = (tempAngle < 0) ? (360 + tempAngle) :  tempAngle;  // 保证是正角度
                    QString text = QString::number(angle / 10);
                    if(angle == 0) text = "N";
                    if(angle == 90) text = "E";
                    if(angle == 180) text = "S";
                    if(angle == 270) text = "W";
                    painter.drawText(textRect, Qt::AlignCenter, text);
                    painter.drawLine(i, 0, i, -15);
                }
                step++;
                tempAngle-=5;
            }
        }
        else if(ones == 5)
        {
            double tempAngle = m_CurrentAngle;
            int step = 2;
            for(int i = 0; i <= width(); i += 50)
            {
                if(step % 2 == 0)
                {
                    painter.drawLine(i, 0, i, -10);
                }
                else
                {
                    QRect textRect(i - 20, -57, 40, 50);
                    int angle = (tempAngle < 0) ? (360 + tempAngle) :  tempAngle;  // 保证是正角度
                    QString text = QString::number(angle / 10);
                    if(angle == 0) text = "N";
                    if(angle == 90) text = "E";
                    if(angle == 180) text = "S";
                    if(angle == 270) text = "W";
                    painter.drawText(textRect, Qt::AlignCenter, text);
                    painter.drawLine(i, 0, i, -15);
                }
                step++;
                tempAngle+=5;
            }
            tempAngle = m_CurrentAngle; // 0
            step = 1;
            for(int i = -50; i >= -width(); i -= 50)
            {
                if(step % 2 == 0)
                {
                    painter.drawLine(i, 0, i, -10);
                }
                else
                {
                    QRect textRect(i - 20, -57, 40, 50);
                    int angle = (tempAngle < 0) ? (360 + tempAngle) :  tempAngle;  // 保证是正角度
                    QString text = QString::number(angle / 10);
                    if(angle == 0) text = "N";
                    if(angle == 90) text = "E";
                    if(angle == 180) text = "S";
                    if(angle == 270) text = "W";
                    painter.drawText(textRect, Qt::AlignCenter, text);
                    painter.drawLine(i, 0, i, -15);
                }
                step++;
                tempAngle-=5;
            }
        }
        else
        {
            double diff = 10 - ones;
            double tempAngle = m_CurrentAngle + diff;
            int step = 1;
            for(int i = diff * 10; i <= width(); i += 50)
            {
                if(step % 2 == 0)
                {
                    painter.drawLine(i, 0, i, -10);
                }
                else
                {
                    QRect textRect(i - 20, -57, 40, 50);
                    int angle = (tempAngle < 0) ? (360 + tempAngle) :  tempAngle;  // 保证是正角度
                    QString text = QString::number(angle / 10);
                    if(angle == 0) text = "N";
                    if(angle == 90) text = "E";
                    if(angle == 180) text = "S";
                    if(angle == 270) text = "W";
                    painter.drawText(textRect, Qt::AlignCenter, text);
                    painter.drawLine(i, 0, i, -15);
                }
                step++;
                tempAngle+=5;
            }
            diff = ones - 5; // 2
            tempAngle = m_CurrentAngle - diff; // 0
            step = 2;
            for(int i = -diff * 10; i >= -width(); i -= 50)
            {
                if(step % 2 == 0)
                {
                    painter.drawLine(i, 0, i, -10);
                }
                else
                {
                    QRect textRect(i - 20, -57, 40, 50);
                    int angle = (tempAngle < 0) ? (360 + tempAngle) :  tempAngle;  // 保证是正角度
                    QString text = QString::number(angle / 10);
                    if(angle == 0) text = "N";
                    if(angle == 90) text = "E";
                    if(angle == 180) text = "S";
                    if(angle == 270) text = "W";
                    painter.drawText(textRect, Qt::AlignCenter, text);
                    painter.drawLine(i, 0, i, -15);
                }
                step++;
                tempAngle-=5;
            }
        }
        // 恢复到之前的坐标系统
        painter.restore();
    }
    pen.setColor(QColor("#0bd612"));
    painter.setPen(pen);
    painter.setBrush(QBrush(QColor(11, 214, 18, 125)));

    QPainterPath path;
    path.moveTo(width() / 2 - 25,10);    // 起点
    path.lineTo(width() / 2 + 25,10);
    path.lineTo(width() / 2 + 25,40);
    path.lineTo(width() / 2 + 10,40);
    path.lineTo(width() / 2,55);
    path.lineTo(width() / 2 - 10,40);
    path.lineTo(width() / 2 - 25,40);
    path.closeSubpath();     // 闭合路径

    painter.drawPath(path);

    pen.setColor(Qt::white);
    painter.setPen(pen);
    QRect textRect(width() / 2 - 25,10, 50, 30);
    painter.drawText(textRect, Qt::AlignCenter, QString::number((double)m_CurrentAngle));
}
