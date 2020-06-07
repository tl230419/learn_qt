#ifndef QT_CONVERSATION_WINDOW_H
#define QT_CONVERSATION_WINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QFontComboBox>
#include <QComboBox>
#include <QToolButton>
#include <QUdpSocket>
#include <QObject>

namespace conversation_window
{

class ConversationWindow : public QMainWindow
{
    enum MSGTYPE
    {
        Enter = 0,
        Exit,
        Msg
    };
Q_OBJECT
public:
    ConversationWindow(QString name, QWidget *parent = Q_NULLPTR);
    ~ConversationWindow();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void conversation_close(QString name, QString time);

private:
    void init_ui();
    void btns_click();
    void socket_operator();
    void send_msg(MSGTYPE type);
    void recv_msg();
    void normal_msg(QString name, QString msg, QString time);
    void enter_msg(QString name);
    void exit_msg(QString name, QString time);

private:
    QTableWidget *tw;
    QPushButton *send_btn;
    QPushButton *exit_btn;
    QLabel *label;
    QTextEdit *msg_edit;
    QTextEdit *send_edit;
    QFontComboBox *font_box;
    QComboBox *font_size_box;
    QToolButton *blod;
    QToolButton *italic;
    QToolButton *under_line;
    QToolButton *font_color;
    QToolButton *save_conversation;
    QToolButton *clear_conversation;
    QUdpSocket *socket;
    QString name;
};

} // namespace conversation_window

#endif // QT_CONVERSATION_WINDOW_H