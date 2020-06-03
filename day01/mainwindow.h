#ifndef QT_MAIN_WINDOW_H
#define QT_MAIN_WINDOW_H

#include <QWidget>
#include "signal_widget.h"
#include "slot_widget.h"

class MainWindow: public QWidget
{
public:
    MainWindow(QWidget* parent = Q_NULLPTR);
    ~MainWindow();

public Q_SLOTS:
    void btn_clicked();

private:
    signal_widget::SignalWidget* signal_widget = nullptr;
    slot_widget::SlotWidget* slot_widget = nullptr;
};

#endif // QT_MAIN_WINDOW_H