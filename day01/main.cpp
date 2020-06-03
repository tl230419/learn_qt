#include <QApplication>
#include <QWidget>
#include "mainwindow.h"
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "main start" << std::endl;

    QApplication app(argc, argv);

    // day01_03_1
//    QWidget w;
//    w.show();

    std::cout << "mainwindow start " << std::endl;
    MainWindow w;
    w.show();
    std::cout << "end" << std::endl;

    return app.exec();
}
