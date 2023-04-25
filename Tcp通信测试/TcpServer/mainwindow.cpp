#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ServerWidget *widget = new ServerWidget(this);
   // widget->show();
    ServerWidget aa;
    aa.setWindowFlags(Qt::Window);
    aa.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

