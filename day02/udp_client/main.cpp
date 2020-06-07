#include "udp_client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    udp_client::UdpClient w;
    w.show();

    return app.exec();
}