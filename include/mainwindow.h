#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tcp_messager.h"

#include <QMainWindow>
#include <QDebug>

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
    /**
     * @brief make slider's value change when spinbox's value changes, so does spinbox
    */
    void syncSpinBoxWithSlider();

    void connectActions();

    void connectTcpMessagerSignals();

    void turnRed();

    void turnGreen();

private:
    Ui::MainWindow *ui;

    Tcp_Messager tcp_client;

private slots:
    void connectToServer();

    void serverConnected();

    void serverDisconnected();

    void on_connect_btn_clicked();

signals:
    void connectTcpServer(QHostAddress, int);
    void disconnectTcpServer();
    void sendMessage(QString);
};
#endif // MAINWINDOW_H
