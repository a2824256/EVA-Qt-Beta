#include "photosviewerwindow.h"
#include "ui_photosviewerwindow.h"
#include <QtWidgets>
#include <string>
#include "common.h"

PhotosViewerWindow::PhotosViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PhotosViewerWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->start(1000);
    setWindowFlags(Qt::FramelessWindowHint);
    page = 1;
    updatePhotoViewer();
}

PhotosViewerWindow::~PhotosViewerWindow()
{
    delete ui;
}

void PhotosViewerWindow::receiveMenu(){
    this->show();
    page = 1;
    updatePhotoViewer();
}


void PhotosViewerWindow::on_returnButton_clicked()
{
    this->hide();
    emit showMenu();
}

void PhotosViewerWindow::receivePhoto(){
    this->show();
}

void PhotosViewerWindow::updatePhotoViewer()
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
    //过滤只要jpg文件
    filters << "*.jpg";
    dir.setNameFilters(filters);
//    文件名
    QStringList list = dir.entryList();
//    总图片数量
    photosNumber = list.count();
//    总页数
    int totalPage = ceil(double(photosNumber)/6);
//    qDebug()<<"totalPage:" + QString::number(totalPage)<<endl;
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

//上一页按钮是否可用状态
void PhotosViewerWindow::preButtonEnable(bool enable){
    if(enable){
        ui->preButton->setEnabled(true);
        ui->preButton->setStyleSheet("background-color:#FF8C00");
    }else{
        ui->preButton->setEnabled(false);
        ui->preButton->setStyleSheet("background-color:#C0C0C0");
    }
}

//下一页按钮是否可用状态
void PhotosViewerWindow::nextButtonEnable(bool enable){
    if(enable){
        ui->nextButton->setEnabled(true);
        ui->nextButton->setStyleSheet("background-color:#FF8C00");
    }else{
        ui->nextButton->setEnabled(false);
        ui->nextButton->setStyleSheet("background-color:#C0C0C0");
    }
}

void PhotosViewerWindow::on_nextButton_clicked()
{
    page+=1;
    updatePhotoViewer();
}

void PhotosViewerWindow::on_preButton_clicked()
{
    if(page>1){
        page-=1;
    }
    updatePhotoViewer();
}

bool PhotosViewerWindow::eventFilter(QObject * watched, QEvent * event){
    if (watched == ui->photoLabel_1 && event->type() == QEvent::MouseButtonPress)
    {
        if(photo_1_path != ""){
//            Qlog("photo_1_path");
            this->hide();
            emit showPhoto(photo_1_path);
        }
    }else if(watched == ui->photoLabel_2 && event->type() == QEvent::MouseButtonPress){
        if(photo_2_path != ""){
//            Qlog("photo_2_path");
            this->hide();
            emit showPhoto(photo_2_path);
        }
    }else if(watched == ui->photoLabel_3 && event->type() == QEvent::MouseButtonPress){
        if(photo_3_path != ""){
//            Qlog("photo_3_path");
            this->hide();
            emit showPhoto(photo_3_path);
        }
    }else if(watched == ui->photoLabel_4 && event->type() == QEvent::MouseButtonPress){
        if(photo_4_path != ""){
//            Qlog("photo_4_path");
            this->hide();
            emit showPhoto(photo_4_path);
        }
    }else if(watched == ui->photoLabel_5 && event->type() == QEvent::MouseButtonPress){
        if(photo_5_path != ""){
//            Qlog("photo_5_path");
            this->hide();
            emit showPhoto(photo_5_path);
        }
    }else if(watched == ui->photoLabel_6 && event->type() == QEvent::MouseButtonPress){
        if(photo_6_path != ""){
//            Qlog("photo_6_path");
            this->hide();
            emit showPhoto(photo_6_path);
        }
    }
    return QWidget::eventFilter(watched, event);
}
