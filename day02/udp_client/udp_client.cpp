#include "udp_client.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

namespace udp_client
{

UdpClient::UdpClient(QWidget *parent)
    : QWidget(parent)
    , socket(nullptr)
{
    socket = new QUdpSocket(this);
    setFixedSize(600, 600);
    setWindowTitle("客户端：6666");
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *hl = new QHBoxLayout;
    QFormLayout *fl = new QFormLayout;

    QLineEdit *ip_edit = new QLineEdit;
    QLineEdit *port_edit = new QLineEdit;
    ip_edit->setText("127.0.0.1");
    port_edit->setText("8888");

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
            recv_msg->append("接收到服务端消息: ");
            recv_msg->append(QString(data));
        }
    });
    connect(send_btn, &QPushButton::clicked, [=](){
        QString ip = ip_edit->text();
        int port = port_edit->text().toInt();
        QString msg = send_msg->toPlainText();
        socket->writeDatagram(msg.toUtf8(), QHostAddress(ip), port);
        send_msg->clear();
    });
    connect(close_btn, &QPushButton::clicked, this, [=](){
        this->close();
    });
    connect(connect_btn, &QPushButton::clicked,this, [=](){
        socket->bind(6666, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
        recv_msg->append("try to connect");
    });
}

UdpClient::~UdpClient()
{

}

} // namespace udp_client
