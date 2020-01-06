#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
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
