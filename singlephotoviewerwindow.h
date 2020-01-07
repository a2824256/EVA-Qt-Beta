#ifndef SINGLEPHOTOVIEWERWINDOW_H
#define SINGLEPHOTOVIEWERWINDOW_H

#include <QMainWindow>

namespace Ui {
class SinglePhotoViewerWindow;
}

class SinglePhotoViewerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SinglePhotoViewerWindow(QWidget *parent = nullptr);
    ~SinglePhotoViewerWindow();

private:
    Ui::SinglePhotoViewerWindow *ui;
};

#endif // SINGLEPHOTOVIEWERWINDOW_H
