#include "menuwindow.h"
#include "ui_menuwindow.h"
#include <QtWidgets>

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::receiveCamera(){
    this->show();
}


void MenuWindow::receiveSetting(){
    this->show();
}


void MenuWindow::on_returnButton_clicked()
{
    this->hide();
    emit showCamera();
}

void MenuWindow::on_settingButton_clicked()
{
    this->hide();
    emit showSetting();
}

void MenuWindow::receivePhotoViewer(){
    this->show();
}

void MenuWindow::receiveVideosViewer(){
    this->show();
}

void MenuWindow::receiveNewMedicalRecord(){
    this->show();
}

void MenuWindow::on_medicalRecordButton_clicked()
{
    this->hide();
    emit showMedicalRecords();
}

void MenuWindow::receiveMedicalRecords(){
    this->show();
}

void MenuWindow::on_dbButton_clicked()
{
    this->hide();
    emit showMultimediaLibrary();
}

void MenuWindow::receiveMedicalLibrary(){
    this->show();
}
