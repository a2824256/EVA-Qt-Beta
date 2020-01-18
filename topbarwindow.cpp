#include "topbarwindow.h"
#include "ui_topbarwindow.h"
#include <QtWidgets>

TopBarWindow::TopBarWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TopBarWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
    show();
    m_timer = new QTimer;
    m_timer->setSingleShot(false);
    m_timer->start(1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));

}

TopBarWindow::~TopBarWindow()
{
    delete ui;
}

void TopBarWindow::timerUpdate(){
    ui->datetime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void TopBarWindow::tipsUpdate(QString content){
    ui->tips->setText("提示:" + content);
}
