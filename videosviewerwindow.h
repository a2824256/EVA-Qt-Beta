#ifndef VIDEOSVIEWERWINDOW_H
#define VIDEOSVIEWERWINDOW_H
#include <iostream>
#include <QMainWindow>
using namespace std;
//#define OPENCV_VIDEOIO_HPP
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

namespace Ui {
class VideosViewerWindow;
}

class VideosViewerWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void showMenu();
    void showVideo(QString VideoPath);

public:
    explicit VideosViewerWindow(QWidget *parent = nullptr);
    ~VideosViewerWindow();    

private:
    Ui::VideosViewerWindow *ui;
    Mat frame;
    QTimer *timer;
    int VideosNumber;
    int page;
    QString path = "/Users/alexleung/Movies";
    QString video_1_path = "";
    QString video_2_path = "";
    QString video_3_path = "";
    QString video_4_path = "";
    QString video_5_path = "";
    QString video_6_path = "";

private slots:
    QImage cvMat2QImage(Mat& mat);
    void receiveMenu();
    void preButtonEnable(bool enable);
    void nextButtonEnable(bool enable);
    void updatePhotoViewer();
    void on_returnButton_clicked();
    void receiveVideoStop();

protected:
    bool eventFilter(QObject * watched, QEvent * event);
};

#endif // VIDEOSVIEWERWINDOW_H
