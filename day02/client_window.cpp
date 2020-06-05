/***********************************
 * Author: Allen
 * Date: 2020-06-05
 ***********************************/
#include "client_window.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

namespace client_window
{

ClientWindow::ClientWindow(QWidget *parent)
    : QWidget(parent)
    , socket(nullptr)
{
    socket = new QTcpSocket(this);
    setFixedSize(600, 600);
    setWindowTitle("客户端");
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *hl = new QHBoxLayout;
    QFormLayout *fl = new QFormLayout;

    QLineEdit *ip_edit = new QLineEdit;
    QLineEdit *port_edit = new QLineEdit;
    ip_edit->setText("127.0.0.1");
    port_edit->setText("6666");

    QPushButton *connect_btn = new QPushButton("连接");
    fl->addRow("服务器IP：", ip_edit);
    fl->addRow("服务器端口：", port_edit);
    hl->addLayout(fl);
    hl->addWidget(connect_btn);

    QTextEdit *recv_msg = new QTextEdit;
    QTextEdit *send_msg = new QTextEdit;
    recv_msg->setEnabled(false);

    QHBoxLayout *btn_layout = new QHBoxLayout;
    QPushButton send_btn = new QPushButton("发送");
    QPushButton close_btn = new QPushButton("关闭");

    layout->addLayout(hl);
    layout->addWidget(recv_msg);
    layout->addWidget(send_msg);
    btn_layout->addWidget(send_btn);
    btn_layout->addWidget(close_btn);
    layout->addLayout(btn_layout);
    setLayout(layout);

    connect(connect_btn, &QPushButton::click,this, [=](){
        QString ip = ip_edit->text();
        quint16 port = port_edit->text().toInt();
        socket->connectToHost(ip, port);
    });
    connect(send_btn, &QTcpSocket::readyRead, this, [=](){
        QByteArray data = socket->readAll();
        recv_msg->append(QString(data));
    });
}

ClientWindow::~ClientWindow() noexcept
{
    if (socket != nullptr)
    {
        delete socket;
        socket = nullptr;
    }
}

} // namespace client_window