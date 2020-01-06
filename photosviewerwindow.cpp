#include "photosviewerwindow.h"
#include "ui_photosviewerwindow.h"

PhotosViewerWindow::PhotosViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PhotosViewerWindow)
{
    ui->setupUi(this);
}

PhotosViewerWindow::~PhotosViewerWindow()
{
    delete ui;
}
