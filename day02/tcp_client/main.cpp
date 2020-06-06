#include "client_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    client_window::ClientWindow w;
    w.show();

    return app.exec();
}