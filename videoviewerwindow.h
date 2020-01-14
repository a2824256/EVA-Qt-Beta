#ifndef VIDEOVIEWERWINDOW_H
#define VIDEOVIEWERWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QVideoWidget>

namespace Ui {
class VideoViewerWindow;
}

class VideoViewerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoViewerWindow(QWidget *parent = nullptr);
    ~VideoViewerWindow();
signals:
    void showVideosViewer();
private:
    Ui::VideoViewerWindow *ui;
    QString _videoPath;
    QMediaPlayer* player;
    QVideoWidget* videoWidget;
    QMediaPlaylist* playlist;
private slots:
    void receiveSingleVideo(QString videoPath);
    void OnStateChanged(QMediaPlayer::State);
protected:
//    bool eventFilter(QObject * watched, QEvent * event);
    void mousePressEvent(QMouseEvent *e);
};

#endif // VIDEOVIEWERWINDOW_H
