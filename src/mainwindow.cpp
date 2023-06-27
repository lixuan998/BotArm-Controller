#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BotArm Controller");
    initUI();
    initConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    turnRed();
}

void MainWindow::initConnections()
{
    syncSpinBoxWithSlider();
    connectActions();
    connectTcpMessagerSignals();
}

void MainWindow::syncSpinBoxWithSlider()
{
    connect(ui->axis0_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis0_slider, &QSlider::setValue);
    connect(ui->axis0_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis0_spinbox, &QSpinBox::setValue);
    connect(ui->axis0_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString tmp_order = "[0," + QString::number(value) + "]";
        emit sendMessage(tmp_order);
    });


    connect(ui->axis1_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis1_slider, &QSlider::setValue);
    connect(ui->axis1_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis1_spinbox, &QSpinBox::setValue);
    connect(ui->axis1_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString tmp_order = "[1," + QString::number(value) + "]";
        emit sendMessage(tmp_order);
    });

    connect(ui->axis2_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis2_slider, &QSlider::setValue);
    connect(ui->axis2_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis2_spinbox, &QSpinBox::setValue);
    connect(ui->axis2_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString tmp_order = "[2," + QString::number(value) + "]";
        emit sendMessage(tmp_order);
    });

    connect(ui->axis3_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis3_slider, &QSlider::setValue);
    connect(ui->axis3_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis3_spinbox, &QSpinBox::setValue);
    connect(ui->axis3_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString tmp_order = "[3," + QString::number(value) + "]";
        emit sendMessage(tmp_order);
    });

    connect(ui->axis4_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis4_slider, &QSlider::setValue);
    connect(ui->axis4_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis4_spinbox, &QSpinBox::setValue);
    connect(ui->axis4_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString tmp_order = "[4," + QString::number(value) + "]";
        emit sendMessage(tmp_order);
    });

    connect(ui->axis5_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis5_slider, &QSlider::setValue);
    connect(ui->axis5_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis5_spinbox, &QSpinBox::setValue);
    connect(ui->axis5_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString tmp_order = "[5," + QString::number(value) + "]";
        emit sendMessage(tmp_order);
    });
}

void MainWindow::connectActions()
{
    connect(ui->connect_to_server_action, &QAction::triggered, this, [&](bool checked){
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->control_action, &QAction::triggered, this, [&]{
        ui->stackedWidget->setCurrentIndex(0);
    });
}

void MainWindow::connectTcpMessagerSignals()
{
    connect(this, &MainWindow::connectTcpServer, &tcp_client, &Tcp_Messager::connectToHost);
    connect(this, &MainWindow::disconnectTcpServer, &tcp_client, &Tcp_Messager::disconnectFromHost);
    connect(&tcp_client, &Tcp_Messager::connected, this, &MainWindow::serverConnected);
    connect(&tcp_client, &Tcp_Messager::disconnected, this, &MainWindow::serverDisconnected);
    connect(this, &MainWindow::sendMessage, &tcp_client, &Tcp_Messager::sendMessage);
}

void MainWindow::connectToServer()
{
    
}

void MainWindow::turnRed()
{
    ui->connect_status_label->setStyleSheet("QLabel{color: rgb(224, 27, 36);}");
    ui->connect_btn->setText("Connect");
    ui->connect_btn->setStyleSheet( "QPushButton{"
                                    "background-color: rgb(165, 29, 45);}"
                                    "QPushButton:hover{"
                                    "background-color: rgb(224, 27, 36);}");
}

void MainWindow::turnGreen()
{
    ui->connect_status_label->setStyleSheet("QLabel{color: rgb(38, 162, 105);}");
    ui->connect_btn->setText("Disconnect");
    ui->connect_btn->setStyleSheet( "QPushButton{"
                                    "background-color: rgb(38, 162, 105);}"
                                    "QPushButton:hover{"
                                    "background-color: rgb(46, 194, 126);}");
}

/**
 * Private Slots
*/

void MainWindow::serverConnected()
{
    turnGreen();
}

void MainWindow::serverDisconnected()
{
    turnRed();
    emit disconnectTcpServer();
}

void MainWindow::on_connect_btn_clicked()
{
    if(ui->connect_btn->text() == "Connect")
        emit connectTcpServer(QHostAddress(ui->ip_lineEdit->text()), (ui->port_lineEdit->text()).toInt());
    else
        emit disconnectTcpServer();
}