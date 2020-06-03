#ifndef QT_SIGNAL_WIDGET_H
#define QT_SIGNAL_WIDGET_H

#include <QObject>

namespace signal_widget
{

class SignalWidget : public QObject
{
Q_OBJECT
public:
    SignalWidget(QObject *parent = Q_NULLPTR);
    ~SignalWidget();

signals:
    void my_signal(int age);

};

} // namespace signal_widget

#endif // QT_SIGNAL_WIDGET_H