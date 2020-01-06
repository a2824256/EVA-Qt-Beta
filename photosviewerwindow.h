#ifndef PHOTOSVIEWERWINDOW_H
#define PHOTOSVIEWERWINDOW_H

#include <QMainWindow>

namespace Ui {
class PhotosViewerWindow;
}

class PhotosViewerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PhotosViewerWindow(QWidget *parent = nullptr);
    ~PhotosViewerWindow();

private:
    Ui::PhotosViewerWindow *ui;
};

#endif // PHOTOSVIEWERWINDOW_H
