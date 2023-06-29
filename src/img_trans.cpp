#include "img_trans.h"

ImgTrans::ImgTrans()
{
    
}
ImgTrans::~ImgTrans()
{
    qDebug() << "ImgTrans resolved successfully";
}
void ImgTrans::transImage(qint16 port)
{
    server = new QTcpServer();
    socket = new QTcpSocket();
    connect(server, &QTcpServer::newConnection, this, &ImgTrans::addConnection);
    qDebug() << "ret" << server->listen(QHostAddress::Any, port);
    qDebug() << "ImgTrans started ? " << server->isListening();
}

/**
 * 
 * private slots
 * 
 */

void ImgTrans::addConnection()
{
    while(server->hasPendingConnections())
    {
        socket = server->nextPendingConnection();
        Device *device = new Device(socket);
        connect(device,&Device::sendMat, this, &ImgTrans::sendMat);
        device_list.push_back(device);
        qDebug() << "income ip: " << socket->localAddress();
    }
}
