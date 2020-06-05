/***********************************
 * Author: Allen
 * Date: 2020-06-05
 ***********************************/
#ifndef QT_CLIENT_WINDOW_H
#define QT_CLIENT_WINDOW_H

#include <QWidget>
#include <QTcpSocket>

namespace client_window
{

class ClientWindow : public QWidget
{
public:
    ClientWindow(QWidget *parent = Q_NULLPTR);
    ~ClientWindow();

private:
    QTcpSocket *socket;

};

} // namespace client_window

#endif // QT_CLIENT_WINDOW_H