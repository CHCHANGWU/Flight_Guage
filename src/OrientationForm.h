#ifndef ORIENTATIONFORM_H
#define ORIENTATIONFORM_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

namespace Ui {
class OrientationForm;
}

class OrientationForm : public QWidget
{
    Q_OBJECT

public:
    explicit OrientationForm(QWidget *parent = nullptr);
    ~OrientationForm();

public slots:
    void setCpmpassAngle(qreal angle);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void drawBackground(QPainter& painter);

private:
    Ui::OrientationForm *ui;
};

#endif // ORIENTATIONFORM_H
