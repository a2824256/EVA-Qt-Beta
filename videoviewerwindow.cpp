#include "videoviewerwindow.h"
#include "ui_videoviewerwindow.h"
#include "common.h"

VideoViewerWindow::VideoViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideoViewerWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    player = new QMediaPlayer;
    videoWidget = new QVideoWidget;
    playlist=new QMediaPlaylist;

    videoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);
    ui->videoOutput->addWidget(videoWidget);
    videoWidget->raise();
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(OnStateChanged(QMediaPlayer::State)));
}

VideoViewerWindow::~VideoViewerWindow()
{
    player->stop();
    delete ui;
}

//当视频播放结束
void VideoViewerWindow::OnStateChanged(QMediaPlayer::State state){
    if(QMediaPlayer::StoppedState == state)
    {
        this->hide();
        emit showVideosViewer();
    }
}

void VideoViewerWindow::receiveSingleVideo(QString videoPath){
    _videoPath = videoPath;
    Qlog(videoPath);
    this->show();

    playlist->clear();
    playlist->addMedia(QUrl::fromLocalFile(videoPath));
    player->setPlaylist(playlist);

    QFile file(videoPath);
    if(!file.open(QIODevice::ReadOnly)) qDebug() << "Could not open file";
    player->setVideoOutput(videoWidget);
    player->setPlaylist(playlist);
    player->play();
}

//bool VideoViewerWindow::eventFilter(QObject * watched, QEvent * event){
//    Qlog("1111111111");
//    if (event->type() == QEvent::MouseButtonPress){
//        this->hide();
//        emit showVideosViewer();
//    }
//    return QWidget::eventFilter(watched, event);
//}

void VideoViewerWindow::mousePressEvent(QMouseEvent *e){
    qDebug()<<e->flags()<<endl;
    player->stop();
}
