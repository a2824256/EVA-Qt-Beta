#ifndef MENUWINDOW_H
#define MENUWINDOW_H
//#include "topbarwindow.h"
#include <QMainWindow>

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void showCamera();
    void showSetting();
    void showPhotoViewer();
    void showVideosViewer();
    void showMedicalRecords();
    void showMultimediaLibrary();

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private:
    Ui::MenuWindow *ui;
    QTimer *timer;
//    TopBarWindow *tbwin;

private slots:
    void receiveNewMedicalRecord();
    void receiveCamera();
    void receiveSetting();
    void receivePhotoViewer();
    void on_returnButton_clicked();
    void on_settingButton_clicked();
    void receiveVideosViewer();
    void receiveMedicalRecords();
    void on_medicalRecordButton_clicked();
    void on_dbButton_clicked();
    void receiveMedicalLibrary();
};

#endif // MENUWINDOW_H
