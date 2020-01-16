#ifndef NEWMEDICALRECORD_H
#define NEWMEDICALRECORD_H

#include <QMainWindow>

namespace Ui {
class newMedicalRecord;
}

class newMedicalRecord : public QMainWindow
{
    Q_OBJECT

signals:
    void showCamera();

public:
    explicit newMedicalRecord(QWidget *parent = nullptr);
    ~newMedicalRecord();
private slots:
    void receiveCamera();

    void Sleep(int msec);

    void on_number_9_Button_clicked();

    void on_number_8_Button_clicked();

    void on_number_7_Button_clicked();

    void on_number_6_Button_clicked();

    void on_number_5_Button_clicked();

    void on_number_4_Button_clicked();

    void on_number_3_Button_clicked();

    void on_number_2_Button_clicked();

    void on_number_1_Button_clicked();

    void on_number_0_Button_clicked();

    void on_horbar_button_clicked();

    void on_point_Button_clicked();

    void on_rollbackButton_clicked();

    void on_confirmButton_clicked();

    void on_returnButton_clicked();

private:
    Ui::newMedicalRecord *ui;
};

#endif // NEWMEDICALRECORD_H
