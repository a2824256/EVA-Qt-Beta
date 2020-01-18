#ifndef SINGLEPHOTOVIEWERWINDOW_H
#define SINGLEPHOTOVIEWERWINDOW_H

#include <QMainWindow>

namespace Ui {
class SinglePhotoViewerWindow;
}

class SinglePhotoViewerWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void showPhotoViewer();

public:
    explicit SinglePhotoViewerWindow(QWidget *parent = nullptr);
    ~SinglePhotoViewerWindow();
private slots:
    void receiveSinglePhoto(QString photoPath);

protected:
    bool eventFilter(QObject * watched, QEvent * event);

private:
    Ui::SinglePhotoViewerWindow *ui;
    QString _photoPath;
    QTimer *timer;
};

#endif // SINGLEPHOTOVIEWERWINDOW_H
