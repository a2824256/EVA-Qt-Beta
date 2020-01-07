#include "singlephotoviewerwindow.h"
#include "ui_singlephotoviewerwindow.h"

SinglePhotoViewerWindow::SinglePhotoViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SinglePhotoViewerWindow)
{
    ui->setupUi(this);
}

SinglePhotoViewerWindow::~SinglePhotoViewerWindow()
{
    delete ui;
}
