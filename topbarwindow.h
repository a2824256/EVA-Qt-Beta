#ifndef TOPBARWINDOW_H
#define TOPBARWINDOW_H

#include <QMainWindow>
#include <QDialog>
namespace Ui {
class TopBarWindow;
}

class TopBarWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TopBarWindow(QWidget *parent = nullptr);
    ~TopBarWindow();

private:
    Ui::TopBarWindow *ui;
    QTimer *m_timer;

private slots:
    void timerUpdate();
    void tipsUpdate(QString content);
};

#endif // TOPBARWINDOW_H
