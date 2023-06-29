#include "mainwindow.h"

#include <QApplication>
#include <QHostAddress>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QHostAddress>("QHostAddress");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    MainWindow w;
    w.show();
    return a.exec();
}
