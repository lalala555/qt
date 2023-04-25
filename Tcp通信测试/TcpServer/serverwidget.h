#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QDialog>
#include "QTcpServer"
#include "QLabel"

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();
private slots:


    void on_pushButton_clicked();

      void on_btn_send_clicked();

private:
    Ui :: ServerWidget *ui;
    QTcpServer* m_s;
    QTcpSocket* m_tcp;
    QLabel* m_status;
};

#endif // SERVERWIDGET_H
