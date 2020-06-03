#ifndef QT_SLOT_WIDGET_H
#define QT_SLOT_WIDGET_H

#include <QObject>

namespace slot_widget
{

class SlotWidget : public QObject
{
    Q_OBJECT
public:
    SlotWidget(QObject *parent = Q_NULLPTR);
    ~SlotWidget();

public Q_SLOTS:
    void my_slot(int age);
};

} // namespace slot_widget

#endif // QT_SLOT_WIDGET_H