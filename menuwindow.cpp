#include "menuwindow.h"
#include "ui_menuwindow.h"
#include <QtWidgets>

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground, true);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::receiveCamera(){
    this->show();
}


void MenuWindow::receiveSetting(){
    this->show();
}

void MenuWindow::timerUpdate(){
    ui->datetime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}


void MenuWindow::on_returnButton_clicked()
{
    this->hide();
    emit showCamera();
}

void MenuWindow::on_settingButton_clicked()
{
    this->hide();
    emit showSetting();
}

void MenuWindow::on_photosButton_clicked()
{
    this->hide();
    emit showPhotoViewer();
}

void MenuWindow::on_videoButton_clicked()
{

}
