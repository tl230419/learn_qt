/***********************************
 * Author: Allen
 * Date: 2020-06-05
 ***********************************/
#include "server_window.h"
#include <QVBoxLayout>
#include <QPushButton>

namespace server_window
{

ServerWindow::ServerWindow(QWidget *parent)
    : QWidget(parent)
    , recv_msg(nullptr)
    , send_msg(nullptr)
    , socket(nullptr)
{
    setFixedSize(600, 600);
    setWindowTitle("服务器：6666");
    QVBoxLayout *layout = new QVBoxLayout;
    recv_msg = new QTextEdit;
    send_msg = new QTextEdit;

    recv_msg->setEnabled(false);

    QHBoxLayout *btn_layout = QHBoxLayout;
    QPushButton *send_btn = new QPushButton("发送");
    QPushButton *close_btn = new QPushButton("关闭");

    layout->addWidget(recv_msg);
    layout->addWidget(send_msg);
    btn_layout->addWidget(send_btn);
    btn_layout->addWidget(close_btn);
    layout->addLayout(btn_layout);
    setLayout(layout);

    init_socket();
}

ServerWindow::~ServerWindow()
{
    if (server != nullptr)
    {
        delete server;
        server = nullptr;
    }

    if (recv_msg != nullptr)
    {
        delete recv_msg;
        recv_msg = nullptr;
    }

    if (send_msg != nullptr)
    {
        delete send_msg;
        send_msg = nullptr;
    }
}

void ServerWindow::init_socket()
{
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 6666);
    connect(server, &QTcpServer::newConnection, this, &ServerWindow::client_connect_to_server);
}

void ServerWindow::client_connect_to_server()
{
    socket = server->nextPendingConnection();
    QString ip = socket->peerAddress().toString();
    int port = socket->peerPort();
    recv_msg->append(QString("[%1:%2]连接成功").arg(ip).arg(port));
    connect(socket, &QTcpSocket::readyRead, this, &ServerWindow::receive_msg);
}

void ServerWindow::receive_msg()
{
    QByteArray data = socket->readAll();
    recv_msg->append(QString(data));
}

} // namespace server_window