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
    void showPhoto(QString photoPath);

public:
    explicit PhotosViewerWindow(QWidget *parent = nullptr);
    ~PhotosViewerWindow();

private:
    Ui::PhotosViewerWindow *ui;
    QTimer *timer;
    int photosNumber;
    int page;
//    ubuntu系统
//    QString path = "/home/zxbio/图片";
//    mac系统
    QString path = "/Users/alexleung/Pictures";
    QString photo_1_path = "";
    QString photo_2_path = "";
    QString photo_3_path = "";
    QString photo_4_path = "";
    QString photo_5_path = "";
    QString photo_6_path = "";

private slots:
    void preButtonEnable(bool enable);
    void nextButtonEnable(bool enable);
    void receiveMenu();
    void on_returnButton_clicked();
    void updatePhotoViewer();
    void on_nextButton_clicked();
    void on_preButton_clicked();
    void receivePhoto();
protected:
    bool eventFilter(QObject * watched, QEvent * event);
};

#endif // PHOTOSVIEWERWINDOW_H
