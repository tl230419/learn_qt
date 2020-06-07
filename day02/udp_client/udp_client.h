#ifndef QT_UDP_CLIENT_H
#define QT_UDP_CLIENT_H

#include <QWidget>
#include <QUdpSocket>

namespace udp_client
{

class UdpClient : public QWidget
{
    Q_OBJECT
public:
    UdpClient(QWidget *parent = Q_NULLPTR);
    ~UdpClient();

private:
    QUdpSocket *socket;
};

} // namespace udp_client

#endif // QT_UDP_CLIENT_H