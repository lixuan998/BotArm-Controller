#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QResizeEvent>

#include "tcp_messager.h"
#include "img_trans.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    void initUI();
    /**
     * @brief Initializes the connections between various components
    */
    void initConnections();

    void initImgTrans();

    /**
     * @brief make slider's value change when spinbox's value changes, so does spinbox
    */
    void syncSpinBoxWithSlider();

    void connectActions();

    void connectTcpMessagerSignals();
    
    void turnRed();

    void turnGreen();

    void resizeEvent(QResizeEvent * event);

private:
    Ui::MainWindow *ui;

    Tcp_Messager tcp_client;

    cv::Mat cur_mat;

    ImgTrans img_trans;

    QThread img_trans_thread;

private slots:
    void serverConnected();

    void serverDisconnected();

    void showImage(cv::Mat image);

    void on_connect_btn_clicked();

    void on_home_btn_clicked();

signals:
    void connectTcpServer(QHostAddress, int);
    void disconnectTcpServer();
    void sendMessage(QString);
    void setImgTransPort(qint16);
};
#endif // MAINWINDOW_H
