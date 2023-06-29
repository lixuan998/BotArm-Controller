#include "mainwindow.h"
#include "./ui_mainwindow.h"

/**
 * Public functions
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BotArm Controller");
    initUI();
    initConnections();
    initImgTrans();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Private functions
*/
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

void MainWindow::initImgTrans()
{
    connect(&img_trans, &ImgTrans::sendMat, this, &MainWindow::showImage);
    connect(this, &MainWindow::setImgTransPort, &img_trans, &ImgTrans::transImage);
    img_trans.moveToThread(&img_trans_thread);
    img_trans_thread.start();
    emit setImgTransPort(12345);
}

void MainWindow::syncSpinBoxWithSlider()
{
    connect(ui->axis0_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis0_slider, &QSlider::setValue);
    connect(ui->axis0_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis0_spinbox, &QSpinBox::setValue);
    connect(ui->axis0_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString _prefix;
        if(value >= 0) _prefix = "+";
        else
        {
            _prefix = "-";
            value = -value;
        }
        if(abs(value) / 10 == 0) _prefix += "00";
        else if(abs(value) / 100 == 0) _prefix += "0";
        QString tmp_order = "0," + _prefix + QString::number(value);
        emit sendMessage(tmp_order);
    });


    connect(ui->axis1_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis1_slider, &QSlider::setValue);
    connect(ui->axis1_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis1_spinbox, &QSpinBox::setValue);
    connect(ui->axis1_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString _prefix;
        if(value >= 0) _prefix = "+";
        else
        {
            _prefix = "-";
            value = -value;
        }
        if(abs(value) / 10 == 0) _prefix += "00";
        else if(abs(value) / 100 == 0) _prefix += "0";
        QString tmp_order = "1," + _prefix + QString::number(value);
        emit sendMessage(tmp_order);
    });

    connect(ui->axis2_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis2_slider, &QSlider::setValue);
    connect(ui->axis2_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis2_spinbox, &QSpinBox::setValue);
    connect(ui->axis2_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString _prefix;
        if(value >= 0) _prefix = "+";
        else
        {
            _prefix = "-";
            value = -value;
        }
        if(abs(value) / 10 == 0) _prefix += "00";
        else if(abs(value) / 100 == 0) _prefix += "0";
        QString tmp_order = "2," + _prefix + QString::number(value);
        emit sendMessage(tmp_order);
    });

    connect(ui->axis3_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis3_slider, &QSlider::setValue);
    connect(ui->axis3_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis3_spinbox, &QSpinBox::setValue);
    connect(ui->axis3_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString _prefix;
        if(value >= 0) _prefix = "+";
        else
        {
            _prefix = "-";
            value = -value;
        }
        if(abs(value) / 10 == 0) _prefix += "00";
        else if(abs(value) / 100 == 0) _prefix += "0";
        QString tmp_order = "3," + _prefix + QString::number(value);
        emit sendMessage(tmp_order);
    });

    connect(ui->axis4_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis4_slider, &QSlider::setValue);
    connect(ui->axis4_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis4_spinbox, &QSpinBox::setValue);
    connect(ui->axis4_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString _prefix;
        if(value >= 0) _prefix = "+";
        else
        {
            _prefix = "-";
            value = -value;
        }
        if(abs(value) / 10 == 0) _prefix += "00";
        else if(abs(value) / 100 == 0) _prefix += "0";
        QString tmp_order = "4," + _prefix + QString::number(value);
        emit sendMessage(tmp_order);
    });

    connect(ui->axis5_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), ui->axis5_slider, &QSlider::setValue);
    connect(ui->axis5_slider, QOverload<int>::of(&QSlider::valueChanged), ui->axis5_spinbox, &QSpinBox::setValue);
    connect(ui->axis5_slider, QOverload<int>::of(&QSlider::valueChanged), this, [&](int value){
        QString _prefix;
        if(value >= 0) _prefix = "+";
        else
        {
            _prefix = "-";
            value = -value;
        }
        if(abs(value) / 10 == 0) _prefix += "00";
        else if(abs(value) / 100 == 0) _prefix += "0";
        QString tmp_order = "5," + _prefix + QString::number(value);
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

void MainWindow::resizeEvent(QResizeEvent * event)
{
    showImage(cur_mat);
    event->accept();
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

void MainWindow::showImage(cv::Mat image)
{
    cur_mat = image;
    QImage qt_img;
    matToQImage(image, qt_img);
    if(qt_img.isNull()) return;
    QPixmap temp = QPixmap::fromImage(qt_img);
    temp = temp.scaled(ui->display_label->size(), Qt::KeepAspectRatio);
    ui->display_label->setPixmap(temp);
}

void MainWindow::on_connect_btn_clicked()
{
    if(ui->connect_btn->text() == "Connect")
        emit connectTcpServer(QHostAddress(ui->ip_lineEdit->text()), (ui->port_lineEdit->text()).toInt());
    else
        emit disconnectTcpServer();
}