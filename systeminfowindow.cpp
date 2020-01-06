#include "systeminfowindow.h"
#include "ui_systeminfowindow.h"

SystemInfoWindow::SystemInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemInfoWindow)
{
    ui->setupUi(this);
}

SystemInfoWindow::~SystemInfoWindow()
{
    delete ui;
}
