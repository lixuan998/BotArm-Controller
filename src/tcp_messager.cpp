#include "tcp_messager.h"

/**
 * Public Functions
*/
Tcp_Messager::Tcp_Messager()
{
	tcp_server = nullptr;
	tcp_socket = nullptr;
	msg_send_timer = nullptr;
}

Tcp_Messager::~Tcp_Messager()
{
	if(msg_send_timer != nullptr)
	{
		if(msg_send_timer->isActive())
			msg_send_timer->stop();
		delete msg_send_timer;
		msg_send_timer = nullptr;
	}
	if(tcp_server != nullptr)
	{
		if(tcp_server->isListening()) tcp_server->close();
		delete tcp_server;
		tcp_server = nullptr;
	}
	if(tcp_socket != nullptr)
	{
		disconnect(tcp_socket, &QAbstractSocket::readyRead, this, &Tcp_Messager::readData);
		disconnect(tcp_socket, &QAbstractSocket::stateChanged, this, &Tcp_Messager::changeState);
		delete tcp_socket;
		tcp_server = nullptr;
	}
}

/**
 * Private Functions
*/

void Tcp_Messager::connectServerSignals()
{
    connect(tcp_server, &QTcpServer::newConnection, this, &Tcp_Messager::newConnection);
}

void Tcp_Messager::connectClientSignals()
{
	connect(tcp_socket, &QAbstractSocket::readyRead, this, &Tcp_Messager::readData);
	connect(tcp_socket, &QAbstractSocket::stateChanged, this, &Tcp_Messager::changeState);
}

/**
 * Public Slots
*/

void Tcp_Messager::startListening(QHostAddress address, int port)
{
	if (tcp_server == nullptr)
	{
		tcp_server = new QTcpServer();
		connectServerSignals();
	}
    if(!tcp_server->isListening())
    {
        if(tcp_server->listen(QHostAddress(address), port)) emit listening();
    }
	msg_ret_status = true;
	last_order = "";
	if (msg_send_timer == nullptr)
	{
		msg_send_timer = new QTimer();
		msg_send_timer->setInterval(10);
		connect(msg_send_timer, &QTimer::timeout, this, &Tcp_Messager::timeOut);
	}
}
	
void Tcp_Messager::connectToHost(QHostAddress address, int port)
{
	if(tcp_socket != nullptr)
	{
		qDebug() << "delete tcp_socket";
		delete tcp_socket;
		tcp_socket = nullptr;
	}
	
	tcp_socket = new QTcpSocket();

	connectClientSignals();
	tcp_socket->connectToHost(address, port);
	msg_ret_status = true;
	last_order = "";
	if (msg_send_timer == nullptr)
	{
		msg_send_timer = new QTimer();
		msg_send_timer->setInterval(10);
		connect(msg_send_timer, &QTimer::timeout, this, &Tcp_Messager::timeOut);
	}
}

void Tcp_Messager::disconnectFromHost()
{
	qDebug() << "disconnectFromHost";
	if (msg_send_timer != nullptr)
	{
		if(msg_send_timer->isActive())
			msg_send_timer->stop();
		delete msg_send_timer;
		msg_send_timer = nullptr;
	}
	if (tcp_socket != nullptr)
	{
		if (tcp_socket->state() == QAbstractSocket::ConnectedState)
			tcp_socket->disconnectFromHost();			
			
	}
}

void Tcp_Messager::stopListening()
{
	if (msg_send_timer != nullptr)
	{
		if(msg_send_timer->isActive())
			msg_send_timer->stop();
		delete msg_send_timer;
		msg_send_timer = nullptr;
	}
	if (tcp_socket != nullptr)
	{
		if (tcp_socket->state() == QAbstractSocket::ConnectedState)
			tcp_socket->disconnectFromHost();
	}
	if (tcp_server != nullptr)
	{
		if(tcp_server->isListening())  tcp_server->close();
		delete tcp_server;
		tcp_server = nullptr;
	}
   
	
    emit notListening();
}

void Tcp_Messager::sendMessage(QString message)
{
	qDebug() << "msg:: " << message;
    if(tcp_socket == nullptr) return;
    if(tcp_socket->state() != QAbstractSocket::ConnectedState) return;

	msg_mutex.lock();
	msg_queue.push_back(message);
	qDebug() << "msg_send_timer status" << msg_send_timer->isActive();
	if (!msg_send_timer->isActive())
	{
		qDebug() << "activated msg_send_timer";
		msg_send_timer->start();
	}
	msg_mutex.unlock();
}

/**
 * Private Slots
*/

void Tcp_Messager::newConnection()
{
    while(tcp_server->hasPendingConnections())
    {
        tcp_socket = tcp_server->nextPendingConnection();
        emit connected(tcp_socket->peerAddress());
        connect(tcp_socket, &QAbstractSocket::readyRead, this, &Tcp_Messager::readData);
        connect(tcp_socket, &QAbstractSocket::stateChanged, this, &Tcp_Messager::changeState);
    }
}

void Tcp_Messager::changeState(QAbstractSocket::SocketState state)
{
    if(state == QAbstractSocket::ConnectedState)
    {
        emit connected(tcp_socket->peerAddress());
    }
    else if(state == QAbstractSocket::UnconnectedState)
    {
        emit disconnected();
    }
}

void Tcp_Messager::readData()
{
    QByteArray temp = tcp_socket->readAll();
    QString recived_message = temp;
	qDebug() << "rcvd: " << recived_message << " last: " << last_order;
    emit recivedMsg(recived_message);
	status_mutex.lock();
	if (recived_message.contains(last_order) && recived_message.contains("OK")) msg_ret_status = true;
	qDebug() << "status: " << msg_ret_status;
	qDebug() << "A";
	status_mutex.unlock();
}

void Tcp_Messager::timeOut()
{
	qDebug() << "timeout";
	status_mutex.lock();
	msg_mutex.lock();
	qDebug() << "ret_status: " << msg_ret_status;
	if (msg_queue.empty())
	{
		msg_send_timer->stop();
		status_mutex.unlock();
		msg_mutex.unlock();
		return;
	}
	if (!msg_ret_status)
	{
		status_mutex.unlock();
		msg_mutex.unlock();
		return;
	}
	tcp_socket->write(msg_queue.front().toUtf8());
	emit sendMsg(msg_queue.front());
	last_order = msg_queue.front();
	msg_queue.pop_front();
	msg_ret_status = false;
	status_mutex.unlock();
	msg_mutex.unlock();
}