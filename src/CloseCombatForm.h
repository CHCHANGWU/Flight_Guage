#ifndef CLOSECOMBATFORM_H
#define CLOSECOMBATFORM_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

namespace Ui {
class CloseCombatForm;
}

class CloseCombatForm : public QWidget
{
    Q_OBJECT

public:
    explicit CloseCombatForm(QWidget *parent = nullptr);
    ~CloseCombatForm();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void drawBackground(QPainter& painter);

private:
    Ui::CloseCombatForm *ui;
    QPixmap*    m_Fuimage;
};

#endif // CLOSECOMBATFORM_H
