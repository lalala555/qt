#include "mainwindow.h"
#include "serverwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerWidget w;
    w.show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
