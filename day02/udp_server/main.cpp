#include "udp_server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    udp_server::UdpServer w;
    w.show();

    return app.exec();
}