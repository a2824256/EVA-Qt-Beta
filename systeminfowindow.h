#ifndef SYSTEMINFOWINDOW_H
#define SYSTEMINFOWINDOW_H

#include <QMainWindow>

namespace Ui {
class SystemInfoWindow;
}

class SystemInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SystemInfoWindow(QWidget *parent = nullptr);
    ~SystemInfoWindow();

private:
    Ui::SystemInfoWindow *ui;
};

#endif // SYSTEMINFOWINDOW_H
