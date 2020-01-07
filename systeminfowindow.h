#ifndef SYSTEMINFOWINDOW_H
#define SYSTEMINFOWINDOW_H

#include <QMainWindow>

namespace Ui {
class SystemInfoWindow;
}

class SystemInfoWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void showSetting();
public:
    explicit SystemInfoWindow(QWidget *parent = nullptr);
    ~SystemInfoWindow();

private:
    Ui::SystemInfoWindow *ui;
    QTimer *timer;

private slots:
    void timerUpdate();
    void receiveSetting();
    void on_returnButton_clicked();
};

#endif // SYSTEMINFOWINDOW_H
