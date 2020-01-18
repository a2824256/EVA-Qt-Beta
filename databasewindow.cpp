#include "databasewindow.h"
#include "ui_databasewindow.h"
#include "common.h"
#include <string.h>
#include <QtWidgets>
using namespace std;

//上一页按钮是否可用状态
void DatabaseWindow::preButtonEnable(bool enable){
    if(enable){
        ui->preButton->setEnabled(true);
        ui->preButton->setStyleSheet("background-color:#FF8C00");
    }else{
        ui->preButton->setEnabled(false);
        ui->preButton->setStyleSheet("background-color:#C0C0C0");
    }
}

//下一页按钮是否可用状态
void DatabaseWindow::nextButtonEnable(bool enable){
    if(enable){
        ui->nextButton->setEnabled(true);
        ui->nextButton->setStyleSheet("background-color:#FF8C00");
    }else{
        ui->nextButton->setEnabled(false);
        ui->nextButton->setStyleSheet("background-color:#C0C0C0");
    }
}

DatabaseWindow::DatabaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DatabaseWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    pageIndex = 0;
    lookingPath = Common::_multimediaFolderPath;
    updateViewer();
}

DatabaseWindow::~DatabaseWindow()
{
    delete ui;
}

void DatabaseWindow::updateViewer()
{
    qDebug()<<"lookingPath:"<<lookingPath<<endl;
    QDir dir(lookingPath);
    if (!dir.exists()) {
        qDebug()<<"当前目录不存在"<<endl;
        return;
    }
    //设置过滤器
    dir.setFilter(QDir::AllEntries | QDir::NoSymLinks);
    QStringList filters;
    filters << "*.jpg"<<"*.mov"<<"*-ZXBio";
    dir.setNameFilters(filters);
    QStringList list = dir.entryList();
    qDebug()<<"当前路径:"<<dir.path()<<endl;
    qDebug()<<"length:"<<list.length()<<endl;
    VideoCapture cap;
    int counter = 0 + pageIndex * 6;
    QString tempString = "";
    QString tempFileType = "";
    int total = list.count();
//    总页数
    int totalPage = ceil(double(total)/6);
    //file 1
    if(counter<total){
        tempString = list[counter];
        tempFileType = checkFileType(tempString);
        ui->photoLabel_1->installEventFilter(this);
        if(tempFileType == "folder"){
            slot1Type = "folder";
            ui->photoLabel_1->setPixmap(QPixmap(":/images/folder.svg").scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_1->setText(tempString);
        }else if(tempFileType == "jpg"){
            slot1Type = "jpg";
            ui->photoLabel_1->setPixmap(QPixmap(lookingPath + "/" + tempString).scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_1->setText(tempString);
        }else if(tempFileType == "mov"){
            slot1Type = "mov";
            cap.open(QString(lookingPath + "/" + tempString).toStdString());
            cap >> frame;
            ui->photoLabel_1->setPixmap(QPixmap::fromImage(cvMat2QImage(frame)).scaled(QSize(160,100),  Qt::KeepAspectRatio));
            ui->textLabel_1->setText(tempString);
        }else{
            slot1Type = "";
            ui->photoLabel_1->clear();
            ui->textLabel_1->clear();
        }
        counter++;
    }else{
        slot1Type = "";
        ui->photoLabel_1->clear();
        ui->textLabel_1->clear();
    }
    //file 2
    if(counter<total){
        tempString = list[counter];
        tempFileType = checkFileType(tempString);
        ui->photoLabel_2->installEventFilter(this);
        if(tempFileType == "folder"){
            slot2Type = "folder";
            ui->photoLabel_2->setPixmap(QPixmap(":/images/folder.svg").scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_2->setText(tempString);
        }else if(tempFileType == "jpg"){
            slot2Type = "jpg";
            ui->photoLabel_2->setPixmap(QPixmap(lookingPath + "/" + tempString).scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_2->setText(tempString);
        }else if(tempFileType == "mov"){
            slot2Type = "mov";
            cap.open(QString(lookingPath + "/" + tempString).toStdString());
            cap >> frame;
            ui->photoLabel_2->setPixmap(QPixmap::fromImage(cvMat2QImage(frame)).scaled(QSize(160,100),  Qt::KeepAspectRatio));
            ui->textLabel_2->setText(tempString);
        }else{
            slot2Type = "";
            ui->photoLabel_2->clear();
            ui->textLabel_2->clear();
        }
        counter++;
    }else{
        slot2Type = "";
        ui->photoLabel_2->clear();
        ui->textLabel_2->clear();
    }
    //file 3
    if(counter<total){
        tempString = list[counter];
        tempFileType = checkFileType(tempString);
        ui->photoLabel_3->installEventFilter(this);
        if(tempFileType == "folder"){
            slot3Type = "folder";
            ui->photoLabel_3->setPixmap(QPixmap(":/images/folder.svg").scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_3->setText(tempString);
        }else if(tempFileType == "jpg"){
            slot3Type = "jpg";
            ui->photoLabel_3->setPixmap(QPixmap(lookingPath + "/" + tempString).scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_3->setText(tempString);
        }else if(tempFileType == "mov"){
            slot3Type = "mov";
            cap.open(QString(lookingPath + "/" + tempString).toStdString());
            cap >> frame;
            ui->photoLabel_3->setPixmap(QPixmap::fromImage(cvMat2QImage(frame)).scaled(QSize(160,100),  Qt::KeepAspectRatio));
            ui->textLabel_3->setText(tempString);
        }else{
            slot3Type = "";
            ui->photoLabel_3->clear();
            ui->textLabel_3->clear();
        }
        counter++;
    }else{
        slot3Type = "";
        ui->photoLabel_3->clear();
        ui->textLabel_3->clear();
    }
    //file 4
    if(counter<total){
        tempString = list[counter];
        tempFileType = checkFileType(tempString);
        ui->photoLabel_4->installEventFilter(this);
        if(tempFileType == "folder"){
            slot4Type = "folder";
            ui->photoLabel_4->setPixmap(QPixmap(":/images/folder.svg").scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_4->setText(tempString);
        }else if(tempFileType == "jpg"){
            slot4Type = "jpg";
            ui->photoLabel_4->setPixmap(QPixmap(lookingPath + "/" + tempString).scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_4->setText(tempString);
        }else if(tempFileType == "mov"){
            slot4Type = "mov";
            cap.open(QString(lookingPath + "/" + tempString).toStdString());
            cap >> frame;
            ui->photoLabel_4->setPixmap(QPixmap::fromImage(cvMat2QImage(frame)).scaled(QSize(160,100),  Qt::KeepAspectRatio));
            ui->textLabel_4->setText(tempString);
        }else{
            slot4Type = "";
            ui->photoLabel_4->clear();
            ui->textLabel_4->clear();
        }
        counter++;
    }else{
        slot4Type = "";
        ui->photoLabel_4->clear();
        ui->textLabel_4->clear();
    }
    //file 5
    if(counter<total){
        tempString = list[counter];
        tempFileType = checkFileType(tempString);
        ui->photoLabel_5->installEventFilter(this);
        if(tempFileType == "folder"){
            slot5Type = "folder";
            ui->photoLabel_5->setPixmap(QPixmap(":/images/folder.svg").scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_5->setText(tempString);
        }else if(tempFileType == "jpg"){
            slot5Type = "jpg";
            ui->photoLabel_5->setPixmap(QPixmap(lookingPath + "/" + tempString).scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_5->setText(tempString);
        }else if(tempFileType == "mov"){
            slot5Type = "mov";
            cap.open(QString(lookingPath + "/" + tempString).toStdString());
            cap >> frame;
            ui->photoLabel_5->setPixmap(QPixmap::fromImage(cvMat2QImage(frame)).scaled(QSize(160,100),  Qt::KeepAspectRatio));
            ui->textLabel_5->setText(tempString);
        }else{
            slot5Type = "";
            ui->photoLabel_5->clear();
            ui->textLabel_5->clear();
        }
        counter++;
    }else{
        slot5Type = "";
        ui->photoLabel_5->clear();
        ui->textLabel_5->clear();
    }
    //file 6
    if(counter<total){
        tempString = list[counter];
        tempFileType = checkFileType(tempString);
        ui->photoLabel_6->installEventFilter(this);
        if(tempFileType == "folder"){
            slot6Type = "folder";
            ui->photoLabel_6->setPixmap(QPixmap(":/images/folder.svg").scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_6->setText(tempString);
        }else if(tempFileType == "jpg"){
            slot6Type = "jpg";
            ui->photoLabel_6->setPixmap(QPixmap(lookingPath + "/" + tempString).scaled(QSize(160,90),  Qt::KeepAspectRatio));
            ui->textLabel_6->setText(tempString);
        }else if(tempFileType == "mov"){
            slot6Type = "mov";
            cap.open(QString(lookingPath + "/" + tempString).toStdString());
            cap >> frame;
            ui->photoLabel_6->setPixmap(QPixmap::fromImage(cvMat2QImage(frame)).scaled(QSize(160,100),  Qt::KeepAspectRatio));
            ui->textLabel_6->setText(tempString);
        }else{
            slot6Type = "";
            ui->photoLabel_6->clear();
            ui->textLabel_6->clear();
        }
    }else{
        slot6Type = "";
        ui->photoLabel_6->clear();
        ui->textLabel_6->clear();
    }
    //第一页
    if(pageIndex <= 1){
//        Qlog("preButtonEnable false 1");
        preButtonEnable(false);
        if(totalPage<=1){
//            Qlog("nextButtonEnable false 2");
            nextButtonEnable(false);
        }else{
//            Qlog("nextButtonEnable true 3");
            nextButtonEnable(true);
        }
    }
    //最后一页
    if (pageIndex >= totalPage && pageIndex != 1) {
//        Qlog("nextButtonEnable false 4");
        nextButtonEnable(false);
//        Qlog("preButtonEnable true 5");
        preButtonEnable(true);
    }
    //非首页&末页
    if(pageIndex > 1&& pageIndex<totalPage){
//        Qlog("preButtonEnable true 6");
        preButtonEnable(true);
//        Qlog("nextButtonEnable true 7");
        nextButtonEnable(true);
    }
}

QString DatabaseWindow::checkFileType(QString name){
    if(name.contains("ZXBio",Qt::CaseSensitive)) return "folder";
    if(name.contains(".jpg",Qt::CaseSensitive)) return "jpg";
    if(name.contains(".mov",Qt::CaseSensitive)) return "mov";
    return "";
}

//从菜单跳转来的接收函数
void DatabaseWindow::receiveMenu(){
    this->show();
    //初始化翻页
    pageIndex = 0;
    //一进来先把正在打开的目录设置为多媒体库根目录
    lookingPath = Common::_multimediaFolderPath;
}

QImage DatabaseWindow::cvMat2QImage(Mat& mat) //mat to image
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

bool DatabaseWindow::eventFilter(QObject * watched, QEvent * event){
    PrePath = lookingPath;
    if (watched == ui->photoLabel_1 && event->type() == QEvent::MouseButtonPress)
    {
        qDebug()<<"clicked 1"<<endl;
        qDebug()<<"slot1Type:"<<slot1Type<<endl;
        qDebug()<<"photoLabel_1:"<<ui->photoLabel_1->text()<<endl;
        if(slot1Type != ""){
            if(slot1Type == "folder"){
                lookingPath = lookingPath + "/" + ui->textLabel_1->text();
                updateViewer();
            }else if(slot1Type == "jpg"){
                emit showPhoto(lookingPath + "/" + ui->textLabel_1->text());
            }else if(slot1Type == "mov"){
                emit showVideo(lookingPath + "/" + ui->textLabel_1->text());
            }else{

            }
        }
    }else if(watched == ui->photoLabel_2 && event->type() == QEvent::MouseButtonPress){
        if(slot2Type != ""){
            if(slot2Type == "folder"){
                lookingPath = lookingPath + "/" + ui->textLabel_2->text();
                updateViewer();
            }else if(slot2Type == "jpg"){
                emit showPhoto(lookingPath + "/" + ui->textLabel_2->text());
            }else if(slot2Type == "mov"){
                emit showVideo(lookingPath + "/" + ui->textLabel_2->text());
            }else{

            }
        }
    }else if(watched == ui->photoLabel_3 && event->type() == QEvent::MouseButtonPress){
        if(slot3Type != ""){
            if(slot3Type == "folder"){
                lookingPath = lookingPath + "/" + ui->textLabel_3->text();
                updateViewer();
            }else if(slot3Type == "jpg"){
                emit showPhoto(lookingPath + "/" + ui->textLabel_3->text());
            }else if(slot3Type == "mov"){
                emit showVideo(lookingPath + "/" + ui->textLabel_3->text());
            }else{

            }
            this->hide();
        }
    }else if(watched == ui->photoLabel_4 && event->type() == QEvent::MouseButtonPress){
        if(slot4Type != ""){
            if(slot4Type == "folder"){
                lookingPath = lookingPath + "/" + ui->textLabel_4->text();
                updateViewer();
            }else if(slot4Type == "jpg"){
                emit showPhoto(lookingPath + "/" + ui->textLabel_4->text());
            }else if(slot4Type == "mov"){
                emit showVideo(lookingPath + "/" + ui->textLabel_4->text());
            }else{

            }
            this->hide();
        }
    }else if(watched == ui->photoLabel_5 && event->type() == QEvent::MouseButtonPress){
        if(slot5Type != ""){
            if(slot5Type == "folder"){
                lookingPath = lookingPath + "/" + ui->textLabel_5->text();
                updateViewer();
            }else if(slot5Type == "jpg"){
                emit showPhoto(lookingPath + "/" + ui->textLabel_5->text());
            }else if(slot5Type == "mov"){
                emit showVideo(lookingPath + "/" + ui->textLabel_5->text());
            }else{

            }
            this->hide();
        }
    }else if(watched == ui->photoLabel_6 && event->type() == QEvent::MouseButtonPress){
        if(slot6Type != ""){
            if(slot6Type == "folder"){
                lookingPath = lookingPath + "/" + ui->textLabel_6->text();
                updateViewer();
            }else if(slot6Type == "jpg"){
                emit showPhoto(lookingPath + "/" + ui->textLabel_6->text());
            }else if(slot6Type == "mov"){
                emit showVideo(lookingPath + "/" + ui->textLabel_6->text());
            }else{

            }
            this->hide();
        }
    }
    return QWidget::eventFilter(watched, event);
}

void DatabaseWindow::receiveRet(){
    this->show();
}

void DatabaseWindow::splitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}


void DatabaseWindow::on_retButton_clicked()
{
    if(PrePath == Common::_multimediaFolderPath){
        this->hide();
        emit showMenu();
    }else{
        vector<string> pathVector;
        splitString(PrePath.toStdString(), pathVector, "/");
        int size = pathVector.size();
        QString newPath = "";
        for(int i = 0; i < size; i++){
            if(i >= size - 1) break;
            if(pathVector[i] == "") continue;
            newPath += "/" + QString::fromStdString(pathVector[i]);
            qDebug()<<QString::fromStdString(pathVector[i])<<endl;
        }
        lookingPath = newPath;
        updateViewer();
    }
}

void DatabaseWindow::on_preButton_clicked()
{
    if(pageIndex>1){
        pageIndex--;
    }
    updateViewer();
}

void DatabaseWindow::on_nextButton_clicked()
{
    pageIndex++;
    updateViewer();
}
