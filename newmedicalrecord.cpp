#include "newmedicalrecord.h"
#include "ui_newmedicalrecord.h"
#include "common.h"
#include "toast.h"

newMedicalRecord::newMedicalRecord(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newMedicalRecord)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

newMedicalRecord::~newMedicalRecord()
{
    delete ui;
}


void newMedicalRecord::on_number_9_Button_clicked()
{
    ui->textBox->insert("9");
}

void newMedicalRecord::on_number_8_Button_clicked()
{
    ui->textBox->insert("8");
}

void newMedicalRecord::on_number_7_Button_clicked()
{
    ui->textBox->insert("7");
}

void newMedicalRecord::on_number_6_Button_clicked()
{
    ui->textBox->insert("6");
}

void newMedicalRecord::on_number_5_Button_clicked()
{
    ui->textBox->insert("5");
}

void newMedicalRecord::on_number_4_Button_clicked()
{
    ui->textBox->insert("4");
}

void newMedicalRecord::on_number_3_Button_clicked()
{
    ui->textBox->insert("3");
}


void newMedicalRecord::on_number_2_Button_clicked()
{
    ui->textBox->insert("2");
}

void newMedicalRecord::on_number_1_Button_clicked()
{
    ui->textBox->insert("1");
}

void newMedicalRecord::on_number_0_Button_clicked()
{
    ui->textBox->insert("0");
}

void newMedicalRecord::on_horbar_button_clicked()
{
    ui->textBox->insert("-");
}

void newMedicalRecord::on_point_Button_clicked()
{
    ui->textBox->insert(".");
}

void newMedicalRecord::on_rollbackButton_clicked()
{
    QString old_text = ui->textBox->text();
    ui->textBox->setText(old_text.mid(0,old_text.length()-1));
}

void newMedicalRecord::on_confirmButton_clicked()
{
    QString tips = "";
    if(ui->textBox->text() != ""){
        Common::_medicalNumber = ui->textBox->text();
        tips = "病历编号已更新！";
        Common::_tips = "提示:当前病历编号"+ Common::_medicalNumber;
        Toast::showTip(tips, nullptr);
        this->hide();
        emit showMenu();
    }else{
        tips = "病历编号为空";
        Toast::showTip(tips, nullptr);
    }
}

void newMedicalRecord::on_returnButton_clicked()
{
    this->hide();
    emit showMenu();
}

void newMedicalRecord::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void newMedicalRecord::receiveMenu(){
    this->show();
}
