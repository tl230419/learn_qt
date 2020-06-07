#include "udp_server.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

namespace udp_server
{

UdpServer::UdpServer(QWidget *parent)
    : QWidget(parent)
    , socket(nullptr)
{
    socket = new QUdpSocket(this);
    setFixedSize(600, 600);
    setWindowTitle("服务端：8888");
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *hl = new QHBoxLayout;
    QFormLayout *fl = new QFormLayout;

    QLineEdit *ip_edit = new QLineEdit;
    QLineEdit *port_edit = new QLineEdit;
    ip_edit->setText("127.0.0.1");
    port_edit->setText("6666");

    QPushButton *connect_btn = new QPushButton("连接");

    fl->addRow("连接IP：", ip_edit);
    fl->addRow("连接端口：", port_edit);
    hl->addLayout(fl);
    hl->addWidget(connect_btn);

    QTextEdit *recv_msg = new QTextEdit;
    QTextEdit *send_msg = new QTextEdit;

    recv_msg->setEnabled(false);

    QHBoxLayout *btn_layout = new QHBoxLayout;
    QPushButton *send_btn = new QPushButton("发送");
    QPushButton *close_btn = new QPushButton("关闭");

    layout->addLayout(hl);
    layout->addWidget(recv_msg);
    layout->addWidget(send_msg);
    btn_layout->addWidget(send_btn);
    btn_layout->addWidget(close_btn);
    layout->addLayout(btn_layout);
    setLayout(layout);

    connect(socket, &QUdpSocket::readyRead, [=](){
        while(socket->hasPendingDatagrams())
        {
            QByteArray data;
            data.resize(socket->pendingDatagramSize());
            socket->readDatagram(data.data(), data.size());
            recv_msg->append("接收到客户端消息: ");
            recv_msg->append(QString(data));
        }
    });
    connect(close_btn, &QPushButton::clicked, this, [=](){
        this->close();
    });
    connect(connect_btn, &QPushButton::clicked,this, [=](){
        socket->bind(8888, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
        recv_msg->append("try to connect");
    });
    connect(send_btn, &QPushButton::clicked, [=](){
        QString ip = ip_edit->text();
        int port = port_edit->text().toInt();
        QString msg = send_msg->toPlainText();
        socket->writeDatagram(msg.toUtf8(), QHostAddress(ip), port);
        send_msg->clear();
    });
}

UdpServer::~UdpServer() noexcept
{

}

} // namespace udp_server