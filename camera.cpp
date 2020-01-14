/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "camera.h"
#include "ui_camera.h"
#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>
#include <qapplication.h>
#include <QMessageBox>
#include <QPalette>
#include <QtWidgets>

Q_DECLARE_METATYPE(QCameraInfo)
Camera::Camera() : ui(new Ui::Camera)
{
    ui->setupUi(this);

    //Camera devices:
    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : availableCameras) {
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        if (cameraInfo == QCameraInfo::defaultCamera())
            videoDeviceAction->setChecked(true);
    }

    connect(videoDevicesGroup, &QActionGroup::triggered, this, &Camera::updateCameraDevice);

    setCamera(QCameraInfo::defaultCamera());
    ui->viewfinder->lower();
    ui->takeImageButton->raise();
    ui->takeImageButton->setFlat(true);
    ui->takeImageButton->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent; }");
    ui->takeImageButton->setFocusPolicy(Qt::NoFocus);
    ui->progressBar->raise();
    ui->datetime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    ui->datetime->raise();
    ui->tips->raise();
    ui->battery->raise();
    ui->tips->raise();

    ui->recordButton->raise();
    ui->menuButton->raise();

    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground, true);
}

void Camera::takephotoButtonStatus(bool enable){
    if(enable){
        QPixmap takephotoEnableSVG("/Users/alexleung/Downloads/qt_project/EVA-Qt-Beta/images/takephoto.svg");
        QIcon takephotoEnableIcon(takephotoEnableSVG);
        ui->takeImageButton->setIcon(takephotoEnableIcon);
    }else{
        QPixmap takephotoEnableSVG("/Users/alexleung/Downloads/qt_project/EVA-Qt-Beta/images/takephoto_disable.svg");
        QIcon takephotoEnableIcon(takephotoEnableSVG);
        ui->takeImageButton->setIcon(takephotoEnableIcon);
    }
}

void Camera::recordButtonStatus(bool enable){
    if(enable){
        QPixmap recordEnableSVG("/Users/alexleung/Downloads/qt_project/EVA-Qt-Beta/images/recording.svg");
        QIcon recordEnableIcon(recordEnableSVG);
        ui->recordButton->setIcon(recordEnableIcon);
    }else{
        QPixmap recordEnableSVG("/Users/alexleung/Downloads/qt_project/EVA-Qt-Beta/images/record.svg");
        QIcon recordEnableIcon(recordEnableSVG);
        ui->recordButton->setIcon(recordEnableIcon);
    }
}

void Camera::timerUpdate(){
    ui->datetime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void Camera::setCamera(const QCameraInfo &cameraInfo)
{
    m_camera.reset(new QCamera(cameraInfo));

    connect(m_camera.data(), &QCamera::stateChanged, this, &Camera::updateCameraState);
    connect(m_camera.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &Camera::displayCameraError);

    m_mediaRecorder.reset(new QMediaRecorder(m_camera.data()));
    connect(m_mediaRecorder.data(), &QMediaRecorder::stateChanged, this, &Camera::updateRecorderState);

    m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));

    connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this, &Camera::updateRecordTime);
    connect(m_mediaRecorder.data(), QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
            this, &Camera::displayRecorderError);

    m_mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));

//    connect(ui->exposureCompensation, &QAbstractSlider::valueChanged, this, &Camera::setExposureCompensation);

    m_camera->setViewfinder(ui->viewfinder);

    updateCameraState(m_camera->state());
    updateLockStatus(m_camera->lockStatus(), QCamera::UserRequest);
    updateRecorderState(m_mediaRecorder->state());

    connect(m_imageCapture.data(), &QCameraImageCapture::readyForCaptureChanged, this, &Camera::readyForCapture);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageCaptured, this, &Camera::processCapturedImage);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageSaved, this, &Camera::imageSaved);
    connect(m_imageCapture.data(), QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
            this, &Camera::displayCaptureError);

    connect(m_camera.data(), QOverload<QCamera::LockStatus, QCamera::LockChangeReason>::of(&QCamera::lockStatusChanged),
            this, &Camera::updateLockStatus);

//    ui->captureWidget->setTabEnabled(0, (m_camera->isCaptureModeSupported(QCamera::CaptureStillImage)));
//    ui->captureWidget->setTabEnabled(1, (m_camera->isCaptureModeSupported(QCamera::CaptureVideo)));

    updateCaptureMode(0);
    m_camera->start();
}

void Camera::keyPressEvent(QKeyEvent * event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        displayViewfinder();
        m_camera->searchAndLock();
        event->accept();
        break;
    case Qt::Key_Camera:
        if (m_camera->captureMode() == QCamera::CaptureStillImage) {
            takeImage();

        } else {
            if (m_mediaRecorder->state() == QMediaRecorder::RecordingState)
                stop();
            else
                record();
        }
        event->accept();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void Camera::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        m_camera->unlock();
        break;
    default:
        QMainWindow::keyReleaseEvent(event);
    }
}

void Camera::updateRecordTime()
{
    QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
//    ui->statusbar->showMessage(str);
}

void Camera::processCapturedImage(int requestId, const QImage& img)
{
    Q_UNUSED(requestId);
    QImage scaledImage = img.scaled(ui->viewfinder->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));

    // Display captured image for 4 seconds.
    displayCapturedImage();
    QTimer::singleShot(4000, this, &Camera::displayViewfinder);
}

void Camera::configureCaptureSettings()
{
    switch (m_camera->captureMode()) {
    case QCamera::CaptureStillImage:
//        configureImageSettings();
        break;
    case QCamera::CaptureVideo:
//        configureVideoSettings();
        break;
    default:
        break;
    }
}

//void Camera::configureVideoSettings()
//{
//    VideoSettings settingsDialog(m_mediaRecorder.data());
//    settingsDialog.setWindowFlags(settingsDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);

//    settingsDialog.setAudioSettings(m_audioSettings);
//    settingsDialog.setVideoSettings(m_videoSettings);
//    settingsDialog.setFormat(m_videoContainerFormat);

//    if (settingsDialog.exec()) {
//        m_audioSettings = settingsDialog.audioSettings();
//        m_videoSettings = settingsDialog.videoSettings();
//        m_videoContainerFormat = settingsDialog.format();

//        m_mediaRecorder->setEncodingSettings(
//                    m_audioSettings,
//                    m_videoSettings,
//                    m_videoContainerFormat);

//        m_camera->unload();
//        m_camera->start();
//    }
//}

//void Camera::configureImageSettings()
//{
//    ImageSettings settingsDialog(m_imageCapture.data());
//    settingsDialog.setWindowFlags(settingsDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);

//    settingsDialog.setImageSettings(m_imageSettings);

//    if (settingsDialog.exec()) {
//        m_imageSettings = settingsDialog.imageSettings();
//        m_imageCapture->setEncodingSettings(m_imageSettings);
//    }
//}

void Camera::setMuted(bool muted)
{
    m_mediaRecorder->setMuted(muted);
}

void Camera::toggleLock()
{
    switch (m_camera->lockStatus()) {
    case QCamera::Searching:
    case QCamera::Locked:
        m_camera->unlock();
        break;
    case QCamera::Unlocked:
        m_camera->searchAndLock();
    }
}

void Camera::updateLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason)
{
    QColor indicationColor = Qt::black;

    switch (status) {
    case QCamera::Searching:
        indicationColor = Qt::yellow;
//        ui->statusbar->showMessage(tr("Focusing..."));
//        ui->lockButton->setText(tr("Focusing..."));
        break;
    case QCamera::Locked:
        indicationColor = Qt::darkGreen;
//        ui->lockButton->setText(tr("Unlock"));
//        ui->statusbar->showMessage(tr("Focused"), 2000);
        break;
    case QCamera::Unlocked:
        indicationColor = reason == QCamera::LockFailed ? Qt::red : Qt::black;
//        ui->lockButton->setText(tr("Focus"));
//        if (reason == QCamera::LockFailed)
//            ui->statusbar->showMessage(tr("Focus Failed"), 2000);
    }

//    QPalette palette = ui->lockButton->palette();
//    palette.setColor(QPalette::ButtonText, indicationColor);
//    ui->lockButton->setPalette(palette);
}

void Camera::takeImage()
{
    m_isCapturingImage = true;
    m_imageCapture->capture();
}

void Camera::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    m_isCapturingImage = false;
}

void Camera::startCamera()
{
    m_camera->start();
}

void Camera::stopCamera()
{
    m_camera->stop();
}

void Camera::record()
{
    if(m_mediaRecorder->state() == QMediaRecorder::RecordingState){
        stop();
    }else{
        updateCaptureMode(1);
        m_mediaRecorder->record();
        updateRecordTime();
    }
}

void Camera::pause()
{
    m_mediaRecorder->pause();
}

void Camera::stop()
{
    m_mediaRecorder->stop();
    updateCaptureMode(0);
}

void Camera::updateCaptureMode(int mode)
{
    QCamera::CaptureModes captureMode = mode == 0 ? QCamera::CaptureStillImage : QCamera::CaptureVideo;
    if(mode == 0){
        CaptureVideoMode = "image";
    }else{
        CaptureVideoMode = "video";
    }
    if (m_camera->isCaptureModeSupported(captureMode))
        m_camera->setCaptureMode(captureMode);
}

void Camera::updateCameraState(QCamera::State state)
{
    switch (state) {
    case QCamera::ActiveState:
        ui->actionStartCamera->setEnabled(false);
        ui->actionStopCamera->setEnabled(true);
//        ui->captureWidget->setEnabled(true);
        ui->actionSettings->setEnabled(true);
        break;
    case QCamera::UnloadedState:
    case QCamera::LoadedState:
        ui->actionStartCamera->setEnabled(true);
        ui->actionStopCamera->setEnabled(false);
//        ui->captureWidget->setEnabled(false);
        ui->actionSettings->setEnabled(false);
    }
}

void Camera::updateRecorderState(QMediaRecorder::State state)
{
    switch (state) {
    case QMediaRecorder::StoppedState:
        ui->recordButton->setEnabled(true);
//        ui->pauseButton->setEnabled(true);
//        ui->stopButton->setEnabled(false);
        break;
    case QMediaRecorder::PausedState:
        ui->recordButton->setEnabled(true);
//        ui->pauseButton->setEnabled(false);
//        ui->stopButton->setEnabled(true);
        break;
    case QMediaRecorder::RecordingState:
        ui->recordButton->setEnabled(false);
//        ui->pauseButton->setEnabled(true);
//        ui->stopButton->setEnabled(true);
        break;
    }
}

void Camera::setExposureCompensation(int index)
{
    m_camera->exposure()->setExposureCompensation(index*0.5);
}

void Camera::displayRecorderError()
{
    QMessageBox::warning(this, tr("Capture Error"), m_mediaRecorder->errorString());
}

void Camera::displayCameraError()
{
    QMessageBox::warning(this, tr("Camera Error"), m_camera->errorString());
}

void Camera::updateCameraDevice(QAction *action)
{
    setCamera(qvariant_cast<QCameraInfo>(action->data()));
}

void Camera::displayViewfinder()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Camera::displayCapturedImage()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Camera::readyForCapture(bool ready)
{
    ui->takeImageButton->setEnabled(ready);
}

void Camera::addMask(QPixmap& pm, const QString& text)
{
    QPainter painter(&pm);
    painter.setFont(QFont("微软雅黑", 25, QFont::Thin));
    painter.setPen(QColor(255, 255, 0));
    painter.drawText(990, 38, text);
    painter.setPen(QColor(255, 255, 255));
    painter.drawText(55, 38, "ZXBIOMED");
    painter.drawPixmap(5, 5,50,50,QPixmap(":/images/logo.png"));
}

//图片保存在
void Camera::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    latestImagePath = QDir::toNativeSeparators(fileName);
//    qDebug()<<QDir::toNativeSeparators(fileName)<<endl;
    m_isCapturingImage = false;
    if (m_applicationExiting){
        close();
    }
    QString path = QDir::toNativeSeparators(latestImagePath);
    QPixmap qpm(path);
    addMask(qpm,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    qpm.save(&file, "JPEG");
    file.close();
    ui->tips->setText(tr("提示:图片已保存至\"%1\"").arg(latestImagePath));
}

void Camera::closeEvent(QCloseEvent *event)
{
    if (m_isCapturingImage) {
        setEnabled(false);
        m_applicationExiting = true;
        event->ignore();
    } else {
        event->accept();
    }
}

void Camera::on_menuButton_clicked()
{
    this->hide();
    emit showMenu();
}

void  Camera::receiveMenu(){
    this->show();
}
