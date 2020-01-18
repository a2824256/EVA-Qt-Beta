#include "singlephotoviewerwindow.h"
#include "ui_singlephotoviewerwindow.h"
#include "common.h"

SinglePhotoViewerWindow::SinglePhotoViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SinglePhotoViewerWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    timer = new QTimer(this);
    timer->start(1000);
//    Qlog(_photoPath);
//    QPixmap pixmap(_photoPath);
//    QPixmap realPixmap = pixmap.scaled(QSize(320,180),  Qt::KeepAspectRatio);
//    ui->photoLabel->setPixmap(realPixmap);
//    ui->photoLabel->show();
}

SinglePhotoViewerWindow::~SinglePhotoViewerWindow()
{
    delete ui;
}


void SinglePhotoViewerWindow::receiveSinglePhoto(QString photoPath){
    _photoPath = photoPath;
//    Qlog(_photoPath);
    QPixmap pixmap(_photoPath);
    QPixmap realPixmap = pixmap.scaled(QSize(640,360),  Qt::KeepAspectRatio);
    ui->photoLabel->setPixmap(realPixmap);
    ui->photoLabel->show();
    ui->photoLabel->installEventFilter(this);
    show();
}

bool SinglePhotoViewerWindow::eventFilter(QObject * watched, QEvent * event){
    if (watched == ui->photoLabel && event->type() == QEvent::MouseButtonPress)
    {
        this->hide();
        emit showPhotoViewer();
    }
    return QWidget::eventFilter(watched, event);
}

