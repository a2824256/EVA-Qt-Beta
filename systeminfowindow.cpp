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
}

SystemInfoWindow::~SystemInfoWindow()
{
    delete ui;
}
