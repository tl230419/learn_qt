#include "mainwindow.h"
#include <iostream>
#include <QPushButton>
#include <QApplication>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(600, 600);
//    QPushButton btn("按钮");
//    btn.setParent(this);
//    QPushButton *btn = new QPushButton("按钮", this);
//    btn->setParent(this);

//    QPushButton *btn = new QPushButton("退出程序", this);
//    btn->setParent(this);

//    QPushButton *btn = new QPushButton("发送信号", this);
//    btn->setParent(this);
//    connect(btn, &QPushButton::clicked, this, &MainWindow::btn_clicked);
//
//    signal_widget = new signal_widget::SignalWidget(this);
//    slot_widget = new slot_widget::SlotWidget(this);
//    connect(signal_widget, &signal_widget::SignalWidget::my_signal, slot_widget, &slot_widget::SlotWidget::my_slot);

    QLabel *label = new QLabel(this);
    QPixmap *map = new QPixmap(":/image/6.png");
    label->setPixmap(*map);
}

void MainWindow::btn_clicked()
{
//    QApplication::quit();
    emit signal_widget->my_signal(30);
}

MainWindow::~MainWindow()
{

}