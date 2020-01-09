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

public:
    explicit VideosViewerWindow(QWidget *parent = nullptr);
    ~VideosViewerWindow();

private:
    Ui::VideosViewerWindow *ui;
    Mat frame;
    QTimer *timer;
    int photosNumber;
    int page;
    QString path = "/Users/alexleung/Movies";
    QString photo_1_path = "";
    QString photo_2_path = "";
    QString photo_3_path = "";
    QString photo_4_path = "";
    QString photo_5_path = "";
    QString photo_6_path = "";

private slots:
    QImage cvMat2QImage(Mat& mat);
    void timerUpdate();
    void receiveMenu();
    void preButtonEnable(bool enable);
    void nextButtonEnable(bool enable);
    void updatePhotoViewer();
};

#endif // VIDEOSVIEWERWINDOW_H
