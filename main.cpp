#include "widget.h"
#include <QtGui>
#include <QApplication>

QWidget *winMain;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    winMain = &w;
    w.show();

    return a.exec();
}
