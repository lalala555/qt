#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/m4.ico"));
    setWindowTitle("client");
    ui->disconnect->setDisabled(true); // 初始时 ，断开连接按钮不可用

    ui->port->setText("61022"); // 默认端口
    ui->ip->setText("192.168.9.214"); // 默认ip
    ui->msg->setPlaceholderText("please enter");

    // 创建通信的套接字
    m_tcp =new QTcpSocket(this);

    // 接受到服务端消息
    connect(m_tcp,&QTcpSocket::readyRead,this,[=](){
        QByteArray data = m_tcp->readAll();
        ui->record->append("server:" + data);
        // readData();
     });

    // 服务器端断开连接
    connect(m_tcp,&QTcpSocket::disconnected ,this,[=](){
        m_tcp->close();
        //m_tcp->deleteLater(); // 封装 delete
        m_status->setPixmap(QPixmap(":/red.png").scaled(20,20));
        ui->record->append("已经和服务器断开连接....");

        ui->connect->setDisabled(false);// 设置连接按钮不可用
        ui->disconnect->setDisabled(true);
    });

    // 检测连接状态
    connect(m_tcp,&QTcpSocket::connected ,this,[this](){
        m_status->setPixmap(QPixmap(":/green.png").scaled(20,20));
        ui->record->append("success...");

        ui->connect->setDisabled(true);
        ui->disconnect->setDisabled(false);
    });

    // 状态栏
    m_status = new QLabel;
    m_status->setPixmap(QPixmap(":/red.png").scaled(20,20));
    ui->statusBar->addWidget(new QLabel("连接状态： "));
    ui->statusBar->addWidget(m_status);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readData()
{
    QByteArray byteArray;//临时变量,用来存储每次从机械臂读进来的数据
    byteArray.resize(this->m_tcp->bytesAvailable());//先设置每次读取的大小为可接收缓存的大小
    int byteRead = this->m_tcp->read(byteArray.data(), byteArray.size());//把缓存区所有数据读取回来,可以用readAll替代,但是现在用的函数可以判断读取结果

    if (byteRead == -1) {//读取错误
        ui->record->append("read data from robot error!") ;
        return;
    } else if (byteRead == 0) {//没读到东西
        ui->record->append("read data from robot error!") ;
        return;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int aa = 0;
}

// 发送数据按钮
void MainWindow::on_pushButton_clicked()
{
    QString msg = ui->msg->toPlainText();
    m_tcp->write(msg.toUtf8()+"\n"); // 输入客户端
    ui->record->append("client:" + msg);
    ui->msg->clear();
}

// 连接服务器按钮
void MainWindow::on_connect_clicked()
{
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    m_tcp->connectToHost(QHostAddress(ip) , port);
}

// 断开连接
void MainWindow::on_disconnect_clicked()
{
    m_tcp->close();
    ui->disconnect->setDisabled(true);
    ui->connect->setDisabled(false);
}
