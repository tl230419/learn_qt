#include "mainwindow.h"
#include <iostream>
#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QToolBox>
#include <QTableWidget>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // day02_01_1
    /*
    QVBoxLayout *layout = new QVBoxLayout;
    QGroupBox *box1 = new QGroupBox;
    QVBoxLayout *layout1 = new QVBoxLayout;
    box1->setLayout(layout1);

    QGroupBox *box2 = new QGroupBox;
    QVBoxLayout *layout2 = new QVBoxLayout;
    box2->setLayout(layout2);

    QRadioButton *btn1 = new QRadioButton("抽烟");
    QRadioButton *btn2 = new QRadioButton("喝酒");
    QRadioButton *btn3 = new QRadioButton("烫头");

    QRadioButton *btn4 = new QRadioButton("男");
    QRadioButton *btn5 = new QRadioButton("女");
    QRadioButton *btn6 = new QRadioButton("妖");

    layout1->addWidget(btn1);
    layout1->addWidget(btn2);
    layout1->addWidget(btn3);

    layout2->addWidget(btn4);
    layout2->addWidget(btn5);
    layout2->addWidget(btn6);

    layout->addWidget(box1);
    layout->addWidget(box2);

    setLayout(layout);
     */

    // day02_01_2
    /*
    QVBoxLayout *layout = new QVBoxLayout;
    QToolBox *box = new QToolBox;

    QGroupBox *gb1 = new QGroupBox;
    QVBoxLayout *layout1 = new QVBoxLayout;
    gb1->setLayout(layout1);
    QLabel *label1 = new QLabel("张三");
    QLabel *label2 = new QLabel("李四");
    QLabel *label3 = new QLabel("王五");
    layout1->addWidget(label1);
    layout1->addWidget(label2);
    layout1->addWidget(label3);

    QGroupBox *gb2 = new QGroupBox;
    QVBoxLayout *layout2 = new QVBoxLayout;
    gb2->setLayout(layout2);
    QLabel *label4 = new QLabel("周期");
    QLabel *label5 = new QLabel("粥吧");
    QLabel *label6 = new QLabel("周秋");
    layout2->addWidget(label4);
    layout2->addWidget(label5);
    layout2->addWidget(label6);

    box->addItem(gb1, "初中同学");
    box->addItem(gb2, "高中同学");

    layout->addWidget(box);
    setLayout(layout);
    */

    // dy02_01_3
    /*
    QTableWidget *w = new QTableWidget(4, 4, this);
    w->setFixedSize(600, 600);
    QStringList l{"姓名", "年纪", "成绩", "性别"};
    w->setHorizontalHeaderLabels(l);

    QTableWidgetItem *item1 = new QTableWidgetItem("张三");
    QTableWidgetItem *item2 = new QTableWidgetItem("30");
    w->setItem(0, 0, item1);
    w->setItem(0, 1, item2);
    */

    const char *btn_text[20] =
    {
            "7", "8", "9", "+", "(",
            "4", "5", "6", "-", ")",
            "1", "2", "3", "*", "<-",
            "0", ".", "=", "/", "C"
    };

    QVBoxLayout *layout = new QVBoxLayout;
    QLineEdit *edit = new QLineEdit;
    layout->addWidget(edit);

    QGridLayout *layout1 = new QGridLayout;
    for (int i = 0; i < sizeof(btn_text) / sizeof(btn_text[0]); i++)
    {
        QPushButton *btn = new QPushButton(btn_text[i]);
        layout1->addWidget(btn, i / 5, i % 5);
    }
    layout->addLayout(layout1);
    setLayout(layout);
}

MainWindow::~MainWindow()
{

}