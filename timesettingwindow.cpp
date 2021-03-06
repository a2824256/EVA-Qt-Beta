#include "timesettingwindow.h"
#include "ui_timesettingwindow.h"
#include <QtWidgets>

TimeSettingWindow::TimeSettingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimeSettingWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->start(1000);
    setWindowFlags(Qt::FramelessWindowHint);
}

TimeSettingWindow::~TimeSettingWindow()
{
    delete ui;
}



void TimeSettingWindow::receiveSetting(){
    this->show();
}

void TimeSettingWindow::on_returnButton_clicked()
{
    this->hide();
    emit showSetting();
}
