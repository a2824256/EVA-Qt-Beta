#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QtWidgets>

SettingWindow::SettingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->start(1000);
    setWindowFlags(Qt::FramelessWindowHint);
}


SettingWindow::~SettingWindow()
{
    delete ui;
}


void SettingWindow::on_returnButton_clicked()
{
    this->hide();
    emit showMenu();
}

void  SettingWindow::receiveMenu(){
    this->show();
}

void SettingWindow::on_systemInfoButton_clicked()
{
    this->hide();
    emit showSystemInfo();
}

void SettingWindow::on_timeButton_clicked()
{
    this->hide();
    emit showTimeSetting();
}

void SettingWindow::receiveTimeSetting(){
    this->show();
}

void SettingWindow::receiveSystemInfo(){
    this->show();
}



