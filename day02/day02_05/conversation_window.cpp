#include "conversation_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QFileDialog>
#include <QDateTime>

namespace conversation_window
{

ConversationWindow::ConversationWindow(QString name, QWidget *parent)
    : name(name)
    , QMainWindow(parent)
    , tw(nullptr)
    , send_btn(nullptr)
    , exit_btn(nullptr)
    , label(nullptr)
    , msg_edit(nullptr)
    , send_edit(nullptr)
    , font_box(nullptr)
    , font_size_box(nullptr)
    , blod(nullptr)
    , italic(nullptr)
    , under_line(nullptr)
    , font_color(nullptr)
    , save_conversation(nullptr)
    , clear_conversation(nullptr)
{
    this->resize(740, 450);
    init_ui();
    btns_click();
    socket_operator();
}

ConversationWindow::~ConversationWindow() noexcept
{

}

void ConversationWindow::init_ui()
{
    QVBoxLayout *whole_layout = new QVBoxLayout;
    QVBoxLayout *left_layout = new QVBoxLayout;
    tw = new QTableWidget(0, 1);
    tw->setMaximumWidth(180);
    tw->setHorizontalHeaderLabels(QStringList{"用户名"});

    QHBoxLayout *up_layout = new QHBoxLayout;
    QHBoxLayout *down_layout = new QHBoxLayout;
    send_btn = new QPushButton("发送");
    label = new QLabel("在线人数：1");
    exit_btn = new QPushButton("退出");

    msg_edit = new QTextEdit;
    msg_edit->setReadOnly(true);
    QHBoxLayout *icon_layout = new QHBoxLayout;
    send_edit = new QTextEdit;

    font_box = new QFontComboBox;
    font_size_box = new QComboBox;
    blod = new QToolButton;
    italic = new QToolButton;
    under_line = new QToolButton;
    font_color = new QToolButton;
    save_conversation = new QToolButton;
    clear_conversation = new QToolButton;

    blod->setCheckable(true);
    italic->setCheckable(true);
    under_line->setCheckable(true);

    icon_layout->addWidget(font_box);
    icon_layout->addWidget(font_size_box);
    icon_layout->addWidget(blod);
    icon_layout->addWidget(italic);
    icon_layout->addWidget(under_line);
    icon_layout->addWidget(font_color);
    icon_layout->addWidget(save_conversation);
    icon_layout->addWidget(clear_conversation);

    left_layout->addWidget(msg_edit);
    left_layout->addLayout(icon_layout);
    left_layout->addWidget(send_edit);

    up_layout->addLayout(left_layout);
    up_layout->addWidget(tw);
    down_layout->addStretch(1);
    down_layout->addWidget(send_btn);
    down_layout->addStretch(1);
    down_layout->addWidget(label);
    down_layout->addStretch(1);
    down_layout->addWidget(exit_btn);
    down_layout->addStretch(1);

    whole_layout->addLayout(up_layout);
    whole_layout->addLayout(down_layout);

    QWidget *w = new QWidget;
    w->setLayout(whole_layout);
    setCentralWidget(w);

    font_size_box->addItem("12");
    font_size_box->addItem("13");
    font_size_box->addItem("14");
    font_size_box->addItem("15");
    blod->setIconSize(QSize(26, 26));
    italic->setIconSize(QSize(26, 26));
    under_line->setIconSize(QSize(26, 26));
    font_color->setIconSize(QSize(26, 26));
    save_conversation->setIconSize(QSize(26, 26));
    clear_conversation->setIconSize(QSize(26, 26));
    blod->setIcon(QPixmap(":/images/blod.png"));
    italic->setIcon(QPixmap(":/images/italic.png"));
    under_line->setIcon(QPixmap(":/images/under_line.png"));
    font_color->setIcon(QPixmap(":/images/font_color.png"));
    save_conversation->setIcon(QPixmap(":/images/save_conversation.png"));
    clear_conversation->setIcon(QPixmap(":/images/save_conversation.png"));
}

void ConversationWindow::btns_click()
{
    connect(font_box, &QFontComboBox::currentFontChanged, [=](const QFont &font){
        send_edit->setFont(font);
    });
    void (QComboBox::*current_index_changed)(const QString &text) = &QComboBox::currentIndexChanged;
    connect(font_size_box, current_index_changed, [=](const QString &text){
        send_edit->setFontPointSize(text.toDouble());
    });
    connect(blod, &QToolButton::clicked, [=](bool checked = false){
        if (checked)
        {
            send_edit->setFontWeight(QFont::Bold);
        }
        else
        {
            send_edit->setFontWeight(QFont::Bold);
        }
    });
    connect(italic, &QToolButton::clicked, [=](bool checked = false){
        if (checked)
        {
            send_edit->setFontItalic(true);
        }
        else
        {
            send_edit->setFontItalic(false);
        }
    });
    connect(under_line, &QToolButton::clicked, [=](bool checked = false){
        if (checked)
        {
            send_edit->setFontItalic(true);
        }
        else
        {
            send_edit->setFontItalic(false);
        }
    });
    connect(font_color, &QPushButton::clicked, [=](){
        QColor color = QColorDialog::getColor();
        send_edit->setTextColor(color);
    });
    connect(save_conversation, &QToolButton::clicked, [=](){
        QString path = QFileDialog::getSaveFileName(this, "请选择保存的文件名", "./", "TXT(*.txt*)");
        if (path.isEmpty())
        {
            return;
        }

        QFile f(path);
        f.open(QIODevice::WriteOnly);
        QString msg = msg_edit->toPlainText();
        f.write(msg.toUtf8().data());
        f.close();
    });
    connect(clear_conversation, &QToolButton::clicked, [=](){
        msg_edit->clear();
    });
}

void ConversationWindow::socket_operator()
{
    socket = new QUdpSocket(this);
    socket->bind(6666, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    connect(send_btn, &QPushButton::clicked, [=](){
        send_msg(Msg);
    });
    connect(socket, &QUdpSocket::readyRead, [=](){
        recv_msg();
    });

    send_msg(Enter);
    connect(exit_btn, &QPushButton::clicked, [=](){
        close();
    });
}

void ConversationWindow::send_msg(MSGTYPE type)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << type << name;
    if (type == Msg)
    {
        QString msg = send_edit->toPlainText();
        out << msg;
    }
    socket->writeDatagram(data, QHostAddress::Broadcast, 6666);
}

void ConversationWindow::recv_msg()
{
    qDebug() << "接收到消息：" << name << endl;
    QByteArray data;
    data.resize(socket->pendingDatagramSize());
    socket->readDatagram(data.data(), data.length());
    QDataStream ds(&data, QIODevice::ReadOnly);

    int type;
    ds >> type;
    QString name, msg;
    ds >> name;
    QString time = QDateTime().currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    switch (type)
    {
        case Msg:
            ds >> msg;
            normal_msg(name, msg, time);
            break;
        case Enter:
            enter_msg(name);
            break;
        case Exit:
            exit_msg(name, time);
        default:
            return;
    }
}

void ConversationWindow::normal_msg(QString name, QString msg, QString time)
{
    msg_edit->setTextColor(Qt::blue);
    msg_edit->append(QString("[%1]%2").arg(name).arg(time));
    msg_edit->append(msg);
    send_edit->clear();
}

void ConversationWindow::enter_msg(QString name)
{
    if (tw->findItems(name, Qt::MatchExactly).isEmpty())
    {
        msg_edit->setTextColor(Qt::green);
        msg_edit->append(QString("%1上线").arg(name));
        QTableWidgetItem *item = new QTableWidgetItem(name);
        tw->insertRow(0);
        tw->setItem(0, 0, item);

        label->setText(QString("在线人数：%1").arg(tw->rowCount()));
        send_msg(Enter);
    }
}

void ConversationWindow::exit_msg(QString name, QString time)
{
    if (!tw->findItems(name, Qt::MatchExactly).isEmpty())
    {
        msg_edit->setTextColor(Qt::red);
        msg_edit->append(QString("%1 于%2 离开").arg(name).arg(time));

        int row = tw->findItems(name, Qt::MatchExactly).first()->row();
        tw->removeRow(row);

        label->setText(QString("在线人数：%1").arg(tw->rowCount()));
    }
}

void ConversationWindow::closeEvent(QCloseEvent *event)
{
    send_msg(Exit);
    QString time = QDateTime().currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    emit conversation_close(name, time);
}

} // namespace conversation_window