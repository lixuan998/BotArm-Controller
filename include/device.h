#pragma once

#include <QTcpSocket>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <iostream>

#include "opencv_headers.h"
#include "defs.h"

class Device : public QObject{
    Q_OBJECT
    public:
        Device(QTcpSocket *socket);
        ~Device();
    private:
        void connectSocketSignals();
    
    private:
        QTcpSocket *socket;
        QByteArray tmp_data;
        Cargo cargo;

    private slots:
        void readSocket();

    signals:
        void sendMat(cv::Mat);
};