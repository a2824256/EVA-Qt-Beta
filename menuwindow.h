#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void showCamera();
    void showSetting();

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private:
    Ui::MenuWindow *ui;
    QTimer *timer;

private slots:
    void timerUpdate();
    void receiveCamera();
    void receiveSetting();

    void on_returnButton_clicked();
    void on_settingButton_clicked();
};

#endif // MENUWINDOW_H
