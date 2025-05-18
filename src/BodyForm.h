#ifndef BODYFORM_H
#define BODYFORM_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

namespace Ui {
class BodyForm;
}

class BodyForm : public QWidget
{
    Q_OBJECT

public:
    explicit BodyForm(QWidget *parent = nullptr);
    ~BodyForm();


protected:
    void paintEvent(QPaintEvent *event);

private:
    void drawBackground(QPainter& painter);


private:
    Ui::BodyForm *ui;
    QPixmap*    m_Ceimage;
    QPixmap*    m_Fuimage;
};

#endif // BODYFORM_H
