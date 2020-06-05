#ifndef QT_MAIN_WINDOW_H
#define QT_MAIN_WINDOW_H

#include <QWidget>
#include <QTimer>
#include "server_window.h"
#include "client_window.h"

class MainWindow: public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = Q_NULLPTR);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void draw_scale(QPainter &painter);
    void draw_second(QPainter &painter);
    void draw_min(QPainter &painter);
    void draw_hour(QPainter &painter);

private:
    QTimer t;
//    client_window::ClientWindow *client;
    server_window::ServerWindow *server;

};

#endif // QT_MAIN_WINDOW_H