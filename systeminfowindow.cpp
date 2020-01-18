#include "systeminfowindow.h"
#include "ui_systeminfowindow.h"
#include "common.h"
#include <QtWidgets>

SystemInfoWindow::SystemInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemInfoWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->start(1000);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->software_version->setText("软件版本: Ver." + Common::_softwareVersion);
    ui->hardware_version->setText("硬件版本: Ver." + Common::_hardwareVersion);
    ui->batch_number->setText("批次:" + Common::_batchNumber);
    ui->serial_number->setText("序列号:" + Common::_serialNumber);
}

SystemInfoWindow::~SystemInfoWindow()
{
    delete ui;
}



void SystemInfoWindow::receiveSetting(){
    this->show();
}

void SystemInfoWindow::on_returnButton_clicked()
{
    this->hide();
    emit showSetting();
}
