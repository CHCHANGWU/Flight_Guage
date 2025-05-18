#include "StatusForm.h"
#include "ui_StatusForm.h"

StatusForm::StatusForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StatusForm)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);

    m_MainWarninTimer = new QTimer(this);
    m_FlightWarningTimer = new QTimer(this);
    m_FireWarningTimer = new QTimer(this);

    connect(m_MainWarninTimer,&QTimer::timeout,[=](){
        if(m_MainWarningColor == Qt::green || m_MainWarningColor == Qt::black)
        {
            m_MainWarningColor = Qt::red;
            update();
            return;
        }
        if(m_MainWarningColor == Qt::red)
        {
            m_MainWarningColor = Qt::black;
            update();
        }
    });

    connect(m_FlightWarningTimer,&QTimer::timeout,[=](){
        if(m_FlightWarningColor == Qt::green || m_FlightWarningColor == Qt::black)
        {
            m_FlightWarningColor = Qt::red;
            update();
            return;
        }
        if(m_FlightWarningColor == Qt::red)
        {
            m_FlightWarningColor = Qt::black;
            update();
        }
    });

    connect(m_FireWarningTimer,&QTimer::timeout,[=](){
        if(m_FireWarningColor == Qt::green || m_FireWarningColor == Qt::black)
        {
            m_FireWarningColor = Qt::red;
            update();
            return;
        }
        if(m_FireWarningColor == Qt::red)
        {
            m_FireWarningColor = Qt::black;
            update();
        }
    });
}

StatusForm::~StatusForm()
{
    delete ui;
}

void StatusForm::setLeftEnginePower(qreal value)
{
    m_LeftAngle = value;
    update();
}

void StatusForm::setrightEnginePower(qreal value)
{
    m_RightAngle = value;
    update();
}

void StatusForm::setWarning(WARNINGTYPE type)
{
    switch (type) {
    case E_MAINWARNING:
        m_MainWarninTimer->start(500);
        break;
    case E_FLIGHTWARNING:
        m_FlightWarningTimer->start(500);
        break;
    case E_FIREWARNING:
        m_FireWarningTimer->start(500);
        break;
    default:
        break;
    }
}

void StatusForm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

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
    // 右边线
    painter.drawLine(QPoint(w - 1, 0), QPoint(w - 1, h));

    drawEnginePower(painter,E_LEFTENGINE);
    drawEnginePower(painter,E_RIGHTENGINE);

    drawWarning(painter);

}

void StatusForm::drawEnginePower(QPainter &painter, ENGINETYPE type)
{
    painter.save(); // 保存坐标状态

    int w = 90;
    int h = 90;
    int side = qMin(w, h);
    qreal angle = 0.0;

    switch (type) {
    case E_LEFTENGINE:
        painter.translate(59, 75);  // 移动坐标原点到中心
        angle = m_LeftAngle;
        break;
    case E_RIGHTENGINE:
        painter.translate(159, 75);  // 移动坐标原点到中心
        angle = m_RightAngle;
        break;
    default:
        break;
    }

    painter.scale(side / 200.0, side / 200.0); // 缩放统一坐标系到 200x200

    int radius = 90;

    QRectF arcRect(-radius, -radius, radius * 2, radius * 2);

    // 1️⃣ 黄色圆弧（排除左上1/4，即135°~180°）
    QPen yellowPen(Qt::yellow);
    yellowPen.setWidth(3);
    painter.setPen(yellowPen);
    painter.setBrush(Qt::NoBrush);

    // 画其余3/4圆弧（逆时针方向）
    // Qt弧线起始角是从3点钟方向，逆时针方向角度
    painter.drawArc(arcRect, 0 * 16, 90 * 16);   // 0° ~ 135°
    painter.drawArc(arcRect, 180 * 16, 180 * 16); // 180° ~ 360°

    // 2️⃣ 红色弧线（135°~180°的1/3：也就是15°范围）
    // 起点角度：135° + 15° = 150°
    QPen redPen(Qt::red);
    redPen.setWidth(3);
    painter.setPen(redPen);
    painter.drawArc(arcRect, 180 * 16, -25 * 16); // 注意方向仍是逆时针

    // 3️⃣ 白色指针
    QPen pointerPen(Qt::white);
    pointerPen.setWidth(3);
    painter.setPen(pointerPen);

    // 0° 时指向正上方 → 即 90° 在 Qt 坐标系中是上方
    qreal angleDeg = 90 - angle;  // 转换成 Qt 角度坐标
    qreal angleRad = qDegreesToRadians(angleDeg);
    QPointF endPoint(qCos(angleRad) * radius, -qSin(angleRad) * radius);
    painter.drawLine(QPointF(0, 0), endPoint);

    // 4️⃣ 圆上方绘制文字
    QFont font;
    font.setPointSize(28);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(Qt::white);

    // 文字内容
    QString text = (type == E_LEFTENGINE) ? "左" : "右";

    // 文字位置：圆心上方约 (radius + 20) 距离处，稍微偏移一半宽度使其居中
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(text);

    // 注意：y方向为负是向上
    QPoint textPos(-textWidth / 2, -radius - 30);
    painter.drawText(textPos, text);

    // 5 绘制功率
    QFont powerFont;
    font.setPointSize(24);
    font.setBold(false);
    painter.setFont(font);
    if(angle < 270.0)painter.setPen(Qt::white);
    if(angle > 270.0)painter.setPen(Qt::red);

    // 文字内容
    QString powerText = (type == E_LEFTENGINE) ? QString::asprintf("%05.1f", m_LeftAngle) : QString::asprintf("%05.1f", m_RightAngle);

    // 文字位置：圆心上方约 (radius + 20) 距离处，稍微偏移一半宽度使其居中
    QFontMetrics powerFm(powerFont);
    //int powerTextWidth = fm.horizontalAdvance(powerText);

    // 注意：y方向为负是向上
    QPoint powerTextPos(-radius, -radius + 30);
    painter.drawText(powerTextPos, powerText);

    painter.restore(); // 恢复坐标状态
}

void StatusForm::drawWarning(QPainter &painter)
{
    // 设置字体
    QFont font("黑体", 30);
    painter.setFont(font);

    // 要绘制的文字
    QString text = "主警告";

    // 获取文字的尺寸
    QFontMetrics fm(font);
    QRect textRect = fm.boundingRect(text);

    // 设置文字左上角的位置
    QPoint topLeft(width() / 2 - textRect.width() / 2, 20);
    textRect.moveTopLeft(topLeft);

    int temp = width() / 2 - textRect.width() / 2;

    // 绘制边框
    painter.setPen(m_MainWarningColor);
    painter.drawRect(textRect.adjusted(0, 0, 5, 5)); // 外扩一些，让框大于文字

    // 绘制文字
    painter.setPen(Qt::white);
    painter.drawText(topLeft.x(),topLeft.y() + textRect.height() - 3, text);




    text = "飞控警告";
    textRect = fm.boundingRect(text);
    topLeft.setX(temp - textRect.width() / 4 * 3 - 10);
    topLeft.setY(75);
    textRect.moveTopLeft(topLeft);

    // 绘制边框
    painter.setPen(m_FlightWarningColor);
    painter.drawRect(textRect.adjusted(0, 0, 5, 5)); // 外扩一些，让框大于文字

    // 绘制文字
    painter.setPen(Qt::white);
    painter.drawText(topLeft.x(),topLeft.y() + textRect.height() - 3, text);


    text = "火灾警告";
    textRect = fm.boundingRect(text);
    topLeft.setX(temp + textRect.width() / 4 * 3 - 30);
    topLeft.setY(75);
    textRect.moveTopLeft(topLeft);

    // 绘制边框
    painter.setPen(m_FireWarningColor);
    painter.drawRect(textRect.adjusted(0, 0, 5, 5)); // 外扩一些，让框大于文字

    // 绘制文字
    painter.setPen(Qt::white);
    painter.drawText(topLeft.x(),topLeft.y() + textRect.height() - 3, text);
}
