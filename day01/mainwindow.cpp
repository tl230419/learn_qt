#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    std::cout << "init" << std::endl;
}

MainWindow::~MainWindow()
{

}