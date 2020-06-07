#ifndef QT_MAINWINDOW_H
#define QT_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <vector>
#include <QToolButton>
#include <list>

namespace main_window
{

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private:
    void init_ui();
    void create_contacts(QVBoxLayout *const &layout);
    void contacts_click();

private:
    std::vector<QToolButton*> btns;
    std::vector<bool> is_shows;

};

} // namespace main_window

#endif // QT_MAINWINDOW_H