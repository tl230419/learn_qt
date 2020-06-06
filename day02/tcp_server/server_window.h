/***********************************
 * Author: Allen
 * Date: 2020-06-05
 ***********************************/
#ifndef QT_SERVER_WINDOW_H
#define QT_SERVER_WINDOW_H

#include <QWidget>
#include <QTcpServer>
#include <QTextEdit>
#include <QTcpSocket>

namespace server_window
{

class ServerWindow : public QWidget
{
Q_OBJECT
public:
    ServerWindow(QWidget *parent = Q_NULLPTR);
    ~ServerWindow();

private Q_SLOTS:
    void client_connect_to_server();
    void receive_msg();

private:
    void init_socket();

private:
    QTcpServer *server;
    QTextEdit *recv_msg;
    QTextEdit *send_msg;
    QTcpSocket *socket;

};

} // namespace server_window


#endif // QT_SERVER_WINDOW_H