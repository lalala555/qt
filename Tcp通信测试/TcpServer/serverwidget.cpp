#include "serverwidget.h"
#include "ui_serverwidget.h"
#include "QTcpServer"
#include "QTcpSocket"
#include "QHostAddress"
#include "QHostInfo"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
        setWindowTitle("server");
      //  ui->btn_send->setDisabled(true); // 初始化连接前，不能按发送按钮

        m_s = new QTcpServer(this);// 创建监听的套接字

        ui->lineEdit_2->setText("61022"); // 默认资源
        connect(m_s ,&QTcpServer::newConnection ,this,[=](){
            // 创建用于通信的套接字
            m_tcp = m_s->nextPendingConnection();

            m_status->setPixmap(QPixmap(":/green.png").scaled(20,20));// 切换状态栏图片
              ui->textBrowser->append("connect success ;;;");

            // 检测是否可以接受数据
            connect(m_tcp,&QTcpSocket::readyRead,this,[=](){
                QByteArray data = m_tcp->readAll();
                ui->textBrowser->append("client:" + data);
            });

            // 断开连接
            connect(m_tcp,&QTcpSocket::disconnected ,this,[=](){
                m_tcp->close();
                m_tcp->deleteLater(); // 封装 delete
                m_status->setPixmap(QPixmap(":/red.png").scaled(20,20));

                ui->pushButton->setDisabled(true);

            });

            // 切换发送按钮状态


        });

        // 状态栏
        m_status = new QLabel;
        m_status->setPixmap(QPixmap(":/red.png").scaled(20,20));
        ui->statusBar->addWidget(new QLabel("连接状态： "));
        ui->statusBar->addWidget(m_status);
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

// 启动监听服务按钮
void ServerWidget::on_pushButton_clicked()
{
    unsigned short port = ui->lineEdit_2->text().toUShort();
    m_s->listen(QHostAddress::Any ,port); // 设置监听
    ui->pushButton->setDisabled(true);

}

// 发送数据按钮
void ServerWidget::on_btn_send_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    m_tcp->write(msg.toUtf8()); // 输入客户端
    ui->textBrowser->append("server " + msg);

}
