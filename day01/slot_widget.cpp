#include "slot_widget.h"
#include <iostream>

namespace slot_widget
{

SlotWidget::SlotWidget(QObject *parent)
    : QObject(parent)
{

}

SlotWidget::~SlotWidget()
{

}

void SlotWidget::my_slot(int age)
{
    std::cout << "recv self define signal, value: " << age << std::endl;
}

} // namespace slot_widget