#include "videosviewerwindow.h"
#include "ui_videosviewerwindow.h"

VideosViewerWindow::VideosViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideosViewerWindow)
{
    ui->setupUi(this);
}

VideosViewerWindow::~VideosViewerWindow()
{
    delete ui;
}
