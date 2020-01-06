#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void showMenu();

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

private slots:
    void on_returnButton_clicked();
    void receiveMenu();
    void timerUpdate();

private:
    Ui::SettingWindow *ui;
    QTimer *timer;
};

#endif // SETTINGWINDOW_H
