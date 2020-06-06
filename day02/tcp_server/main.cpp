#include "server_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    server_window::ServerWindow w;
    w.show();

    return app.exec();
}