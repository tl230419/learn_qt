#include "mainwindow.h"
#include <QToolBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QToolButton>
#include "conversation_window.h"

namespace main_window
{

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(250, 700);
    setWindowTitle("Chat");
    setWindowIcon(QIcon(":images/chat.png"));
    init_ui();
}

MainWindow::~MainWindow() noexcept
{

}

void MainWindow::init_ui()
{
    auto *tb = new QToolBox;
    auto *gb = new QGroupBox;
    auto *vl = new QVBoxLayout;
    tb->addItem(gb, "联系人");
    gb->setLayout(vl);
    setCentralWidget(tb);
    create_contacts(vl);
    for (int i = 0; i < btns.size(); i++)
    {
        is_shows.push_back(false);
    }
    contacts_click();
}

void MainWindow::create_contacts(QVBoxLayout *const &layout)
{
    QList<QString> name_list{"Maker", "水票奇缘", "忆梦如澜", "北京出版人", "Cherry", "淡然", "娇娇girl", "落水无痕",
                             "青墨暖暖"};
    QStringList icon_list{"qt", "spqy", "ymrl", "qq", "Cherry", "dr", "jj", "lswh", "qmnn"};
    for (int i = 0; i < name_list.size(); i++)
    {
        auto *btn = new QToolButton();
        btn->setText(name_list[i]);
        auto *icon = new QPixmap(QString(":/images/%1.png").arg(icon_list[i]));
        btn->setIcon(*icon);

        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btn->resize(210, 70);
        btn->setAutoRaise(true);
        layout->addWidget(btn);
        btns.push_back(btn);
    }
}

void MainWindow::contacts_click()
{
    for (int i = 0; i < btns.size(); i++)
    {
        QToolButton *btn = btns[i];
        connect(btn, &QToolButton::clicked, [=](){
            if (!is_shows[i])
            {
                auto *w = new conversation_window::ConversationWindow(btn->text());
                w->setWindowTitle(btn->text());
                w->setWindowIcon(btn->icon());
                w->setAttribute(Qt::WA_DeleteOnClose);
                w->show();
                is_shows[i] = true;
                connect(w, &conversation_window::ConversationWindow::conversation_close, [=](QString name, QString time){
                    is_shows[i] = false;
                    qDebug() << name << "下线" << endl;
                });
            }
        });
    }
}

} // namespace main_window
