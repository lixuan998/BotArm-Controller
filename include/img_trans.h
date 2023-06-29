#ifndef __IMG_TRAINS_H__
#define __IMG_TRAINS_H__
#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include <QMap>
#include <QDebug>

#include "device.h"

class ImgTrans : public QObject{
    Q_OBJECT
    public:
        ImgTrans();
        ~ImgTrans();
    private:
        
    private:
        QTcpServer *server;
        QTcpSocket *socket;
        QList<Device *> device_list;

    private slots:
        void addConnection();

    public slots:
        void transImage(qint16 port);

    signals:
        void sendMat(cv::Mat);
        
};

#endif // __IMG_TRAINS_H__