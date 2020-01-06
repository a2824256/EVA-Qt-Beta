#include "timesettingwindow.h"
#include "ui_timesettingwindow.h"

TimeSettingWindow::TimeSettingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimeSettingWindow)
{
    ui->setupUi(this);
}

TimeSettingWindow::~TimeSettingWindow()
{
    delete ui;
}
