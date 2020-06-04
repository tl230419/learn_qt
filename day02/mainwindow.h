#ifndef QT_MAIN_WINDOW_H
#define QT_MAIN_WINDOW_H

#include <QWidget>

class MainWindow: public QWidget
{
public:
    MainWindow(QWidget* parent = Q_NULLPTR);
    ~MainWindow();
};

#endif // QT_MAIN_WINDOW_H