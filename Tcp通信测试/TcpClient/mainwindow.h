#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTcpSocket>
#include <QString>
#include <QLabel>
#include <QHostAddress>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void readData();
protected:
    virtual void  resizeEvent(QResizeEvent *event);

private slots:

    void on_pushButton_clicked();

    void on_connect_clicked();

    void on_disconnect_clicked();



private:
    Ui::MainWindow *ui;
    QTcpSocket* m_tcp;
    QLabel* m_status;
};

#endif // MAINWINDOW_H
