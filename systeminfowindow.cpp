#include "systeminfowindow.h"
#include "ui_systeminfowindow.h"
#include <QtWidgets>

SystemInfoWindow::SystemInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemInfoWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    setWindowFlags(Qt::FramelessWindowHint);
}

SystemInfoWindow::~SystemInfoWindow()
{
    delete ui;
}

void SystemInfoWindow::timerUpdate(){
    ui->datetime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void SystemInfoWindow::receiveSetting(){
    this->show();
}

void SystemInfoWindow::on_returnButton_clicked()
{
    this->hide();
    emit showSetting();
}
