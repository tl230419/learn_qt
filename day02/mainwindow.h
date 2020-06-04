#ifndef QT_MAIN_WINDOW_H
#define QT_MAIN_WINDOW_H

#include <QWidget>
#include <QTimer>

class MainWindow: public QWidget
{
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
};

#endif // QT_MAIN_WINDOW_H