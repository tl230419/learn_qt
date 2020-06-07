#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    main_window::MainWindow w;
    w.show();

    return app.exec();
}