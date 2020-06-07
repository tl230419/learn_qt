/*
 * Example from https://www.cnblogs.com/tangxin-blog/p/8283460.html
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QPushButton>
#include <QLineEdit>
#include <QTextBrowser>
#include <QLabel>
#include <QCloseEvent>


class Widget : public QWidget
{
Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QUdpSocket *udpsock;
    QPushButton *btn1,*btn2,*btn3;
    QLineEdit *edit1,*edit2,*edit3;
    QLabel *label1,*label2,*label3;
    QTextBrowser *text1;
    void closeEvent(QCloseEvent *event);
private slots:
    void mybindip();
    void mysenddata();
    void recvmydata();
};

#endif // WIDGET_H