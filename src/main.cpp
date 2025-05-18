#include "MainForm.h"
#include "AttitudeIndicator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainForm w;
    w.show();
    return a.exec();
}
