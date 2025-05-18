#ifndef STATUSFORM_H
#define STATUSFORM_H

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <QColor>
#include <QTimer>

namespace Ui {
class StatusForm;
}

class StatusForm : public QWidget
{
    Q_OBJECT

public:
    enum ENGINETYPE
    {
        E_LEFTENGINE,
        E_RIGHTENGINE,
    };

    enum WARNINGTYPE
    {
        E_MAINWARNING,
        E_FLIGHTWARNING,
        E_FIREWARNING
    };

    explicit StatusForm(QWidget *parent = nullptr);
    ~StatusForm();

public slots:
    void setLeftEnginePower(qreal value);
    void setrightEnginePower(qreal value);

    void setWarning(WARNINGTYPE type);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void drawEnginePower(QPainter& painter,ENGINETYPE type);
    void drawWarning(QPainter& painter);

private:
    Ui::StatusForm *ui;
    qreal m_LeftAngle = 0.0;
    qreal m_RightAngle = 0.0;
    QColor m_MainWarningColor = Qt::green;
    QColor m_FlightWarningColor = Qt::green;
    QColor m_FireWarningColor = Qt::green;
    QTimer* m_MainWarninTimer;
    QTimer* m_FlightWarningTimer;
    QTimer* m_FireWarningTimer;
};

#endif // STATUSFORM_H
