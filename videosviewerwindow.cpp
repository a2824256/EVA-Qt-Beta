#include "videosviewerwindow.h"
#include "ui_videosviewerwindow.h"
#include "QtWidgets"
//#include "opencv.hpp"
//using namespace cv;
//#include "highgui.hpp"
VideosViewerWindow::VideosViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideosViewerWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    VideoCapture cap("/Users/alexleung/Movies/clip_0001.mov");
    cap >> frame;
    QImage phtoto_label_1 = cvMat2QImage(frame);
    QPixmap tempPixmap = QPixmap::fromImage(phtoto_label_1);
    QPixmap realPixmap = tempPixmap.scaled(QSize(160,90),  Qt::KeepAspectRatio);
    ui->photoLabel_1->setPixmap(realPixmap);
}

// OpenCV Mat格式图像转 Qt QImage图像
QImage VideosViewerWindow::cvMat2QImage(Mat& mat) //mat to image
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}
void VideosViewerWindow::receiveMenu(){
    this->show();
}

VideosViewerWindow::~VideosViewerWindow()
{
    delete ui;
}

void VideosViewerWindow::timerUpdate(){
    ui->datetime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

//上一页按钮是否可用状态
void VideosViewerWindow::preButtonEnable(bool enable){
    if(enable){
        ui->preButton->setEnabled(true);
        ui->preButton->setStyleSheet("background-color:#FF8C00");
    }else{
        ui->preButton->setEnabled(false);
        ui->preButton->setStyleSheet("background-color:#C0C0C0");
    }
}

//下一页按钮是否可用状态
void VideosViewerWindow::nextButtonEnable(bool enable){
    if(enable){
        ui->nextButton->setEnabled(true);
        ui->nextButton->setStyleSheet("background-color:#FF8C00");
    }else{
        ui->nextButton->setEnabled(false);
        ui->nextButton->setStyleSheet("background-color:#C0C0C0");
    }
}

void VideosViewerWindow::updatePhotoViewer()
{
    qDebug()<<"page:" + QString::number(page)<<endl;
    //获得目录
    QDir dir(path);
    if (!dir.exists()) {
        qDebug()<<"当前目录不存在"<<endl;
        return;
    }
    //设置过滤器
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    //过滤只要jpg文件
    filters << "*.mov";
    dir.setNameFilters(filters);
//    文件名
    QStringList list = dir.entryList();
//    总图片数量
    photosNumber = list.count();
//    总页数
    int totalPage = ceil(double(photosNumber)/6);
    qDebug()<<"totalPage:" + QString::number(totalPage)<<endl;
    int realPage = page-1;
//    label_1
    if(photosNumber>=1+realPage*6){
        int photoLabel_1_index = 0+realPage*6;
        photo_1_path = path+"/"+list[photoLabel_1_index];
        QPixmap pixmap_1(photo_1_path);
        QPixmap realPixmap_1 = pixmap_1.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_1->setPixmap(realPixmap_1);
        ui->photoLabel_1->show();
        ui->textLabel_1->setText(list[photoLabel_1_index]);
        ui->textLabel_1->show();
        ui->photoLabel_1->installEventFilter(this);
    }else {
        photo_1_path = "";
        ui->photoLabel_1->clear();
        ui->textLabel_1->clear();
    }
//    label_2
    if(photosNumber>=2+realPage*6){
        int photoLabel_2_index = 1+realPage*6;
        photo_2_path = path+"/"+list[photoLabel_2_index];
        QPixmap pixmap_2(photo_2_path);
        QPixmap realPixmap_2 = pixmap_2.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_2->setPixmap(realPixmap_2);
        ui->photoLabel_2->show();
        ui->textLabel_2->setText(list[photoLabel_2_index]);
        ui->textLabel_2->show();
        ui->photoLabel_2->installEventFilter(this);
    }else{
        photo_2_path = "";
        ui->photoLabel_2->clear();
        ui->textLabel_2->clear();
    }
//    label_3
    if(photosNumber>=3+realPage*6){
        int photoLabel_3_index = 2+realPage*6;
        photo_3_path = path+"/"+list[photoLabel_3_index];
        QPixmap pixmap_3(photo_3_path);
        QPixmap realPixmap_3 = pixmap_3.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_3->setPixmap(realPixmap_3);
        ui->photoLabel_3->show();
        ui->textLabel_3->setText(list[photoLabel_3_index]);
        ui->textLabel_3->show();
        ui->photoLabel_3->installEventFilter(this);
    }else{
        photo_3_path = "";
        ui->photoLabel_3->clear();
        ui->textLabel_3->clear();
    }
//    label_4
    if(photosNumber>=4+realPage*6){
        int photoLabel_4_index = 3+realPage*6;
        photo_4_path = path+"/"+list[photoLabel_4_index];
        QPixmap pixmap_4(photo_4_path);
        QPixmap realPixmap_4 = pixmap_4.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_4->setPixmap(realPixmap_4);
        ui->photoLabel_4->show();
        ui->textLabel_4->setText(list[photoLabel_4_index]);
        ui->textLabel_4->show();
        ui->photoLabel_4->installEventFilter(this);
    }else{
        photo_4_path = "";
        ui->photoLabel_4->clear();
        ui->textLabel_4->clear();
    }
//    label_5
    if(photosNumber>=5+realPage*6){
        int photoLabel_5_index = 4+realPage*6;
        photo_5_path = path+"/"+list[photoLabel_5_index];
        QPixmap pixmap_5(photo_5_path);
        QPixmap realPixmap_5 = pixmap_5.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_5->setPixmap(realPixmap_5);
        ui->photoLabel_5->show();
        ui->textLabel_5->setText(list[photoLabel_5_index]);
        ui->textLabel_5->show();
        ui->photoLabel_5->installEventFilter(this);
    }else{
        photo_5_path = "";
        ui->photoLabel_5->clear();
        ui->textLabel_5->clear();
    }
//    label_6
    if(photosNumber>=6+realPage*6){
        int photoLabel_6_index = 5+realPage*6;
        photo_6_path = path+"/"+list[photoLabel_6_index];
        QPixmap pixmap_6(photo_6_path);
        QPixmap realPixmap_6 = pixmap_6.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_6->setPixmap(realPixmap_6);
        ui->photoLabel_6->show();
        ui->textLabel_6->setText(list[photoLabel_6_index]);
        ui->textLabel_6->show();
        ui->photoLabel_6->installEventFilter(this);
    }else{
        photo_6_path = "";
        ui->photoLabel_6->clear();
        ui->textLabel_6->clear();
    }
    //第一页
    if(page <= 1){
//        Qlog("preButtonEnable false 1");
        preButtonEnable(false);
        if(totalPage<=1){
//            Qlog("nextButtonEnable false 2");
            nextButtonEnable(false);
        }else{
//            Qlog("nextButtonEnable true 3");
            nextButtonEnable(true);
        }
    }
    //最后一页
    if (page >= totalPage) {
//        Qlog("nextButtonEnable false 4");
        nextButtonEnable(false);
//        Qlog("preButtonEnable true 5");
        preButtonEnable(true);
    }
    //非首页&末页
    if(page > 1&& page<totalPage){
//        Qlog("preButtonEnable true 6");
        preButtonEnable(true);
//        Qlog("nextButtonEnable true 7");
        nextButtonEnable(true);
    }
}
