#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QtWidgets>

SettingWindow::SettingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
}


SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::timerUpdate(){
    ui->datetime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void SettingWindow::on_returnButton_clicked()
{
    this->hide();
    emit showMenu();
}

void  SettingWindow::receiveMenu(){
    this->show();
}
