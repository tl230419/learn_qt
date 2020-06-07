#include "chat.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHostAddress>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
        : QWidget(parent)
{
    this->setWindowTitle("聊天室");
    udpsock=new QUdpSocket(this);
    //udpsock->bind(8080);
    connect(udpsock,SIGNAL(readyRead()),this,SLOT(recvmydata()));
    label1=new QLabel(tr("发送端口号："));
    edit1=new QLineEdit();
    label2=new QLabel(tr("接收端口号："));
    edit2=new QLineEdit();
    btn1=new QPushButton(tr("绑定"));
    connect(btn1,SIGNAL(clicked()),this,SLOT(mybindip()));

    btn2=new QPushButton(tr("发送"));
    connect(btn2,SIGNAL(clicked()),this,SLOT(mysenddata()));
    label3=new QLabel(tr("消息内容："));
    edit3=new QLineEdit();
    text1=new QTextBrowser();

    QHBoxLayout *lay1=new QHBoxLayout();
    lay1->addWidget(label1);
    lay1->addWidget(edit1);
    lay1->addWidget(label2);
    lay1->addWidget(edit2);
    lay1->addWidget(btn1);

    QHBoxLayout *lay2=new QHBoxLayout();
    lay2->addWidget(label3);
    lay2->addWidget(edit3);
    lay2->addWidget(btn2);
    QVBoxLayout *lay3=new QVBoxLayout(this);
    lay3->addLayout(lay1);
    lay3->addLayout(lay2);
    lay3->addWidget(text1);
}

//绑定接收端口号
void Widget::mybindip()
{
    udpsock->close();
    //获取接收端口号
    QString port1=edit2->text();
    if(port1.isEmpty())
    {
        QMessageBox::critical(this,"错误信息","发送端口号不可以为空！");
        return ;
    }
    udpsock->bind(port1.toInt());
    QMessageBox::information(this,"提示信息","绑定成功！端口号是"+port1);
}

//发送消息
void Widget::mysenddata()
{
    //获取发送端口号
    QString port2=edit1->text();
    if(port2.isEmpty())
    {
        QMessageBox::critical(this,"错误信息","发送端口号不可以为空！");
        return ;
    }
    //获取发送内容
    QString txt=edit3->text();
    char buf[1024]={0};
    strcpy(buf,txt.toStdString().data());
    //定义地址类
    QHostAddress *serip=new QHostAddress();
    serip->setAddress("127.0.0.1");
    udpsock->writeDatagram(buf,strlen(buf),*serip,port2.toInt());
    delete serip;
    edit3->clear();
    edit3->setFocus();
}

//接收消息
void Widget::recvmydata()
{
    QMessageBox::information(this,"提示信息","接收到消息");
    char buf[1024]={0};
    while(udpsock->hasPendingDatagrams())
    {
        udpsock->readDatagram(buf,sizeof(buf));
        text1->append(buf);
        memset(buf,0,sizeof(buf));
    }
}

//关闭
void Widget::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::information(this,"提示信息","确定要退出该程序？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes)
    {
        event->accept();
    }else
    {
        event->ignore();
    }
}

Widget::~Widget()
{

}