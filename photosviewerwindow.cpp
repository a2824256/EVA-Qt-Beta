#include "photosviewerwindow.h"
#include "ui_photosviewerwindow.h"
#include <QtWidgets>

PhotosViewerWindow::PhotosViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PhotosViewerWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    QDir dir(path);
    if (!dir.exists()) {
        return;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    filters << "*.jpg";
    dir.setNameFilters(filters);
//    file list
    QStringList list = dir.entryList();
    if (list.count() <= 0)
    {
        qDebug()<<"number:"<<0<<endl;
    }else{
        qDebug()<<"number:"<<list.count()<<endl;
    }
    setWindowFlags(Qt::FramelessWindowHint);
}

PhotosViewerWindow::~PhotosViewerWindow()
{
    delete ui;
}

void PhotosViewerWindow::receiveMenu(){
    this->show();
}

void PhotosViewerWindow::timerUpdate(){
    ui->datetime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void PhotosViewerWindow::on_returnButton_clicked()
{
    this->hide();
    emit showMenu();
}
