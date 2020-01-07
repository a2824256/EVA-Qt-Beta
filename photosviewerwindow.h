#ifndef PHOTOSVIEWERWINDOW_H
#define PHOTOSVIEWERWINDOW_H

#include <QMainWindow>

namespace Ui {
class PhotosViewerWindow;
}

class PhotosViewerWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void showMenu();

public:
    explicit PhotosViewerWindow(QWidget *parent = nullptr);
    ~PhotosViewerWindow();

private:
    Ui::PhotosViewerWindow *ui;
    QTimer *timer;
    int photosNumber;
    QString path = "/home/zxbio/图片";

private slots:
    void receiveMenu();
    void timerUpdate();
    void on_returnButton_clicked();
};

#endif // PHOTOSVIEWERWINDOW_H
