#ifndef TOAST_H
#define TOAST_H

#include <QMainWindow>

namespace Ui {
class Toast;
}

class Toast : public QMainWindow
{
    Q_OBJECT

public:
    explicit Toast(QWidget *parent = nullptr);
    ~Toast();
    void setText(const QString& text);
    void showAnimation(int timeout = 2000);// 动画方式show出，默认2秒后消失
    static void showTip(const QString& text, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Toast *ui;
};

#endif // TOAST_H
