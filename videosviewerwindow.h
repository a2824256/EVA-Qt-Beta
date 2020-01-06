#ifndef VIDEOSVIEWERWINDOW_H
#define VIDEOSVIEWERWINDOW_H

#include <QMainWindow>

namespace Ui {
class VideosViewerWindow;
}

class VideosViewerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideosViewerWindow(QWidget *parent = nullptr);
    ~VideosViewerWindow();

private:
    Ui::VideosViewerWindow *ui;
};

#endif // VIDEOSVIEWERWINDOW_H
