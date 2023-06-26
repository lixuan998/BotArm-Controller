#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BotArm Controller");
    initConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initConnections()
{
    syncSpinBoxWithSlider();
    connectActions();
}

void MainWindow::syncSpinBoxWithSlider()
{
    connect(ui->axis0_spinbox, SIGNAL(valueChanged(int)), ui->axis0_slider, SLOT(setValue(int)));
    connect(ui->axis0_slider, SIGNAL(valueChanged(int)), ui->axis0_spinbox, SLOT(setValue(int)));

    connect(ui->axis1_spinbox, SIGNAL(valueChanged(int)), ui->axis1_slider, SLOT(setValue(int)));
    connect(ui->axis1_slider, SIGNAL(valueChanged(int)), ui->axis1_spinbox, SLOT(setValue(int)));

    connect(ui->axis2_spinbox, SIGNAL(valueChanged(int)), ui->axis2_slider, SLOT(setValue(int)));
    connect(ui->axis2_slider, SIGNAL(valueChanged(int)), ui->axis2_spinbox, SLOT(setValue(int)));

    connect(ui->axis3_spinbox, SIGNAL(valueChanged(int)), ui->axis3_slider, SLOT(setValue(int)));
    connect(ui->axis3_slider, SIGNAL(valueChanged(int)), ui->axis3_spinbox, SLOT(setValue(int)));

    connect(ui->axis4_spinbox, SIGNAL(valueChanged(int)), ui->axis4_slider, SLOT(setValue(int)));
    connect(ui->axis4_slider, SIGNAL(valueChanged(int)), ui->axis4_spinbox, SLOT(setValue(int)));

    connect(ui->axis5_spinbox, SIGNAL(valueChanged(int)), ui->axis5_slider, SLOT(setValue(int)));
    connect(ui->axis5_slider, SIGNAL(valueChanged(int)), ui->axis5_spinbox, SLOT(setValue(int)));
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
    
}

void MainWindow::connectToServer()
{

}
