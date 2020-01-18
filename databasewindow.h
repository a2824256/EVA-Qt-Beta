#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QMainWindow>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <string.h>
using namespace std;
using namespace cv;

namespace Ui {
class DatabaseWindow;
}

class DatabaseWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void showVideo(QString path);
    void showPhoto(QString path);
    void showMenu();

public:
    explicit DatabaseWindow(QWidget *parent = nullptr);
    ~DatabaseWindow();

private:
    Ui::DatabaseWindow *ui;
    QString lookingPath = "";
    int pageIndex = 0;
    Mat frame;
    QString PrePath = "";
    QString slot1Type = "";
    QString slot2Type = "";
    QString slot3Type = "";
    QString slot4Type = "";
    QString slot5Type = "";
    QString slot6Type = "";


private slots:
    void updateViewer();
    void receiveMenu();
    QString checkFileType(QString name);
    QImage cvMat2QImage(Mat& mat);
    void receiveRet();
    void on_retButton_clicked();
    void splitString(const string& s, vector<string>& v, const string& c);
    void preButtonEnable(bool enable);
    void nextButtonEnable(bool enable);

    void on_preButton_clicked();

    void on_nextButton_clicked();

protected:
    bool eventFilter(QObject * watched, QEvent * event);
};

#endif // DATABASEWINDOW_H
