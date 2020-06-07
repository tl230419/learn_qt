#ifndef QT_UDP_SERVER_H
#define QT_UDP_SERVER_H

#include <QWidget>
#include <QUdpSocket>

namespace udp_server
{

class UdpServer : public QWidget
{

public:
    UdpServer(QWidget *parent = Q_NULLPTR);
    ~UdpServer();

private:
    QUdpSocket *socket;

};

} // namespace udp_server

#endif // QT_UDP_SERVER_H