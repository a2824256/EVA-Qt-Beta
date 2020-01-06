#include "timesettingwindow.h"
#include "ui_timesettingwindow.h"
#include <QtWidgets>

TimeSettingWindow::TimeSettingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimeSettingWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
}

TimeSettingWindow::~TimeSettingWindow()
{
    delete ui;
}
