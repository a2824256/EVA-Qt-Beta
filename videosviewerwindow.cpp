#include "videosviewerwindow.h"
#include "ui_videosviewerwindow.h"
#include "QtWidgets"
#include "common.h"
//#include "opencv.hpp"
//using namespace cv;
//#include "highgui.hpp"
VideosViewerWindow::VideosViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideosViewerWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    page = 1;
    updatePhotoViewer();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    setWindowFlags(Qt::FramelessWindowHint);
}

void VideosViewerWindow::timerUpdate(){
    ui->datetime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
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
//    qDebug()<<"page:" + QString::number(page)<<endl;
    //获得目录
    QDir dir(path);
    if (!dir.exists()) {
        qDebug()<<"当前目录不存在"<<endl;
        return;
    }
    //设置过滤器
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    //过滤只要mov文件
    filters << "*.mov";
    dir.setNameFilters(filters);
    //    文件名
    QStringList list = dir.entryList();
    //    总图片数量
    VideosNumber = list.count();
    //    总页数
    int totalPage = ceil(double(VideosNumber)/6);
//    qDebug()<<"totalPage:" + QString::number(totalPage)<<endl;
    int realPage = page-1;
    //opencv打开视频
//    VideoCapture cap;
/*    cap.open("/Users/alexleung/Movies/clip_0001.mov");
    //截取视频第一帧
    cap >> frame;
    //将Mat数据转为QImage
    QImage phtoto_label_1 = cvMat2QImage(frame);
    //将Qimage转为QPixmap
    QPixmap tempPixmap = QPixmap::fromImage(phtoto_label_1);
    //将图片等比例缩放
    QPixmap realPixmap = tempPixmap.scaled(QSize(160,90),  Qt::KeepAspectRatio);
    ui->photoLabel_1->setPixmap(realPixmap);
    ui->textLabel_1->setText("");*/
    VideoCapture cap;
//    label_1
    if(VideosNumber>=1+realPage*6){
        int photoLabel_1_index = 0+realPage*6;
        video_1_path = path+"/"+list[photoLabel_1_index];
        string video_path = video_1_path.toStdString();
        cap.open(video_path);
        //截取视频第一帧
        cap >> frame;
        //将Mat数据转为QImage
        QImage phtoto_label_1 = cvMat2QImage(frame);
        //将Qimage转为QPixmap
        QPixmap tempPixmap = QPixmap::fromImage(phtoto_label_1);
        //将图片等比例缩放
        QPixmap realPixmap = tempPixmap.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_1->setPixmap(realPixmap);
        ui->photoLabel_1->show();
        ui->textLabel_1->setText(list[photoLabel_1_index]);
        ui->textLabel_1->show();
        ui->photoLabel_1->installEventFilter(this);
    }else {
        video_1_path = "";
        ui->photoLabel_1->clear();
        ui->textLabel_1->clear();
    }
//    label_2
    if(VideosNumber>=2+realPage*6){
        int photoLabel_2_index = 1+realPage*6;
        video_2_path = path+"/"+list[photoLabel_2_index];
        string video_path = video_2_path.toStdString();
        cap.open(video_path);
        //截取视频第一帧
        cap >> frame;
        //将Mat数据转为QImage
        QImage phtoto_label_2 = cvMat2QImage(frame);
        //将Qimage转为QPixmap
        QPixmap tempPixmap = QPixmap::fromImage(phtoto_label_2);
        //将图片等比例缩放
        QPixmap realPixmap_2 = tempPixmap.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_2->setPixmap(realPixmap_2);
        ui->photoLabel_2->show();
        ui->textLabel_2->setText(list[photoLabel_2_index]);
        ui->textLabel_2->show();
        ui->photoLabel_2->installEventFilter(this);
    }else{
        video_2_path = "";
        ui->photoLabel_2->clear();
        ui->textLabel_2->clear();
    }
//    label_3
    if(VideosNumber>=3+realPage*6){
        int photoLabel_3_index = 2+realPage*6;
        video_3_path = path+"/"+list[photoLabel_3_index];
        string video_path = video_3_path.toStdString();
        cap.open(video_path);
        //截取视频第一帧
        cap >> frame;
        //将Mat数据转为QImage
        QImage phtoto_label_3 = cvMat2QImage(frame);
        //将Qimage转为QPixmap
        QPixmap tempPixmap = QPixmap::fromImage(phtoto_label_3);
        //将图片等比例缩放
        QPixmap realPixmap_3 = tempPixmap.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_3->setPixmap(realPixmap_3);
        ui->photoLabel_3->show();
        ui->textLabel_3->setText(list[photoLabel_3_index]);
        ui->textLabel_3->show();
        ui->photoLabel_3->installEventFilter(this);
    }else{
        video_3_path = "";
        ui->photoLabel_3->clear();
        ui->textLabel_3->clear();
    }
//    label_4
    if(VideosNumber>=4+realPage*6){
        int photoLabel_4_index = 3+realPage*6;
        video_4_path = path+"/"+list[photoLabel_4_index];
        string video_path = video_4_path.toStdString();
        cap.open(video_path);
        //截取视频第一帧
        cap >> frame;
        //将Mat数据转为QImage
        QImage phtoto_label_4 = cvMat2QImage(frame);
        //将Qimage转为QPixmap
        QPixmap tempPixmap = QPixmap::fromImage(phtoto_label_4);
        //将图片等比例缩放
        QPixmap realPixmap_4 = tempPixmap.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_4->setPixmap(realPixmap_4);
        ui->photoLabel_4->show();
        ui->textLabel_4->setText(list[photoLabel_4_index]);
        ui->textLabel_4->show();
        ui->photoLabel_4->installEventFilter(this);
    }else{
        video_4_path = "";
        ui->photoLabel_4->clear();
        ui->textLabel_4->clear();
    }
//    label_5
    if(VideosNumber>=5+realPage*6){
        int photoLabel_5_index = 4+realPage*6;
        video_5_path = path+"/"+list[photoLabel_5_index];
        string video_path = video_5_path.toStdString();
        cap.open(video_path);
        //截取视频第一帧
        cap >> frame;
        //将Mat数据转为QImage
        QImage phtoto_label_5 = cvMat2QImage(frame);
        //将Qimage转为QPixmap
        QPixmap tempPixmap = QPixmap::fromImage(phtoto_label_5);
        //将图片等比例缩放
        QPixmap realPixmap_5 = tempPixmap.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_5->setPixmap(realPixmap_5);
        ui->photoLabel_5->show();
        ui->textLabel_5->setText(list[photoLabel_5_index]);
        ui->textLabel_5->show();
        ui->photoLabel_5->installEventFilter(this);
    }else{
        video_5_path = "";
        ui->photoLabel_5->clear();
        ui->textLabel_5->clear();
    }
//    label_6
    if(VideosNumber>=6+realPage*6){
        int photoLabel_6_index = 5+realPage*6;
        video_6_path = path+"/"+list[photoLabel_6_index];
        QPixmap pixmap_6(video_6_path);
        QPixmap realPixmap_6 = pixmap_6.scaled(QSize(160,90),  Qt::KeepAspectRatio);
        ui->photoLabel_6->setPixmap(realPixmap_6);
        ui->photoLabel_6->show();
        ui->textLabel_6->setText(list[photoLabel_6_index]);
        ui->textLabel_6->show();
        ui->photoLabel_6->installEventFilter(this);
    }else{
        video_6_path = "";
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
    if (page >= totalPage && page != 1) {
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
bool VideosViewerWindow::eventFilter(QObject * watched, QEvent * event){
//    qDebug()<<event->type()<<endl;
    if (watched == ui->photoLabel_1 && event->type() == QEvent::MouseButtonPress)
    {
        if(video_1_path != ""){
//            Qlog("photo_1_path");
            this->hide();
            emit showVideo(video_1_path);
        }
    }else if(watched == ui->photoLabel_2 && event->type() == QEvent::MouseButtonPress){
        if(video_2_path != ""){
//            Qlog("photo_2_path");
            this->hide();
            emit showVideo(video_2_path);
        }
    }else if(watched == ui->photoLabel_3 && event->type() == QEvent::MouseButtonPress){
        if(video_3_path != ""){
//            Qlog("photo_3_path");
            this->hide();
            emit showVideo(video_3_path);
        }
    }else if(watched == ui->photoLabel_4 && event->type() == QEvent::MouseButtonPress){
        if(video_4_path != ""){
//            Qlog("photo_4_path");
            this->hide();
            emit showVideo(video_4_path);
        }
    }else if(watched == ui->photoLabel_5 && event->type() == QEvent::MouseButtonPress){
        if(video_5_path != ""){
//            Qlog("photo_5_path");
            this->hide();
            emit showVideo(video_5_path);
        }
    }else if(watched == ui->photoLabel_6 && event->type() == QEvent::MouseButtonPress){
        if(video_6_path != ""){
//            Qlog("photo_6_path");
            this->hide();
            emit showVideo(video_6_path);
        }
    }
    return QWidget::eventFilter(watched, event);
}

void VideosViewerWindow::on_returnButton_clicked()
{
    this->hide();
    emit showMenu();
}

void VideosViewerWindow::receiveVideoStop(){
    this->show();
}
