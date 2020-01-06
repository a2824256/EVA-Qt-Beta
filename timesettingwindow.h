#ifndef TIMESETTINGWINDOW_H
#define TIMESETTINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class TimeSettingWindow;
}

class TimeSettingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TimeSettingWindow(QWidget *parent = nullptr);
    ~TimeSettingWindow();

private:
    Ui::TimeSettingWindow *ui;
};

#endif // TIMESETTINGWINDOW_H
