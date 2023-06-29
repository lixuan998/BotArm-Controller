#include "device.h"

Device::Device(QTcpSocket *socket)
{
    this->socket = socket;
    qDebug() << "====================";
    qDebug() << "new device connected";
    //qDebug() << "IP: " << socket->localAddress();
    qDebug() << "Port: " << socket->localPort();

    connectSocketSignals();
}

Device::~Device()
{
    qDebug() << "Device resolved";
}


void Device::connectSocketSignals()
{
    connect(socket, &QTcpSocket::readyRead, this, &Device::readSocket);
}

void Device::readSocket()
{
    QByteArray buffer = socket->readAll();
    tmp_data.push_back(buffer);

    if(tmp_data.size() >= CARGO_SIZE)
    {
        memcpy(&cargo, tmp_data.data(), CARGO_SIZE);
        qDebug() << "cargo height: " << cargo.height << " cargo width: " << cargo.width;
        cv::Mat mat(cargo.height, cargo.width, cargo.type, (uchar *)cargo.data);

        cv::resize(mat, mat, cv::Size(), 2.0, 2.0);
        cv::flip(mat, mat, 1);
        
        QByteArray tmp = tmp_data.right(tmp_data.size() - CARGO_SIZE);
        tmp_data.clear();
        tmp_data = tmp;
        if((tmp_data.size() % CARGO_SIZE) == 0 && tmp_data.size() >= CARGO_SIZE)
        {
            qDebug() << "CLEAR BUFFEER";
            tmp_data.clear();
        }
    }

}
