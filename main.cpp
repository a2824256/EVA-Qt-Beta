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
#include "menuwindow.h"
#include "settingwindow.h"
#include "settingwindow.h"
#include "systeminfowindow.h"
#include "timesettingwindow.h"
#include "videosettings.h"
//#include "photosviewerwindow.h"
#include "singlephotoviewerwindow.h"
//#include "videosviewerwindow.h"
#include "videoviewerwindow.h"
#include "newmedicalrecord.h"
#include "databasewindow.h"
#include "topbarwindow.h"
#include "common.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //更新多媒体库根目录路径
    updatePath();
    //-------------------页面实例-------------------
    //摄像头浏览页面
    Camera camera;
    //设置页面
    SettingWindow setting;
    //菜单页面
    MenuWindow menu;
    //系统信息页面
    SystemInfoWindow systeminfo;
    //系统时间设置页面
    TimeSettingWindow timesetting;
    //旧图片浏览页
    //PhotosViewerWindow photoviewer;
    //图片浏览页面
    SinglePhotoViewerWindow singlephoto;
    //旧视频浏览页
    //VideosViewerWindow videosviewer;
    //视频播放页面
    VideoViewerWindow videoviewer;
    //病历页面
    newMedicalRecord newmedicalrecord;
    //多媒体数据库
    DatabaseWindow dbwindow;
    //顶部栏创口
    TopBarWindow tbwindows;
    //程序启动显示的第一个页面
    menu.show();
    tbwindows.move(menu.x(),menu.y());
    //-------------------页面跳转-------------------
    //摄像头预览 -> 菜单
    QObject::connect(&camera,SIGNAL(showMenu()),&menu,SLOT(receiveCamera()));
    //菜单 -> 摄像头预览
    QObject::connect(&menu,SIGNAL(showCamera()),&camera,SLOT(receiveMenu()));
    //病历 -> 菜单
    QObject::connect(&newmedicalrecord,SIGNAL(showMenu()),&menu,SLOT(receiveMedicalRecords()));
    //菜单 -> 多媒体库
    QObject::connect(&menu,SIGNAL(showMultimediaLibrary()),&dbwindow,SLOT(receiveMenu()));
    //菜单 -> 病历
    QObject::connect(&menu,SIGNAL(showMedicalRecords()),&newmedicalrecord,SLOT(receiveMenu()));
    //设置 -> 菜单
    QObject::connect(&setting,SIGNAL(showMenu()),&menu,SLOT(receiveSetting()));
    //菜单 -> 设置
    QObject::connect(&menu,SIGNAL(showSetting()),&setting,SLOT(receiveMenu()));
    //设置 -> 系统信息
    QObject::connect(&setting,SIGNAL(showSystemInfo()),&systeminfo,SLOT(receiveSetting()));
    //设置 -> 系统时间设置
    QObject::connect(&setting,SIGNAL(showTimeSetting()),&timesetting,SLOT(receiveSetting()));
    //系统时间设置 -> 设置
    QObject::connect(&timesetting,SIGNAL(showSetting()),&setting,SLOT(receiveTimeSetting()));
    //系统设置 -> 设置
    QObject::connect(&systeminfo,SIGNAL(showSetting()),&setting,SLOT(receiveSystemInfo()));
    //多媒体库 -> 菜单
    QObject::connect(&dbwindow,SIGNAL(showMenu()),&menu,SLOT(receiveMedicalLibrary()));
    //视频播放结束返回多媒体库
    QObject::connect(&videoviewer,SIGNAL(showVideosViewer()),&dbwindow,SLOT(receiveRet()));
    //跳转+视频路径传递
    QObject::connect(&dbwindow,SIGNAL(showVideo(QString)),&videoviewer,SLOT(receiveSingleVideo(QString)));
    //跳转+图片路径传递
    QObject::connect(&dbwindow,SIGNAL(showPhoto(QString)),&singlephoto,SLOT(receiveSinglePhoto(QString)));
    //-------------------各页面与顶部栏消息连接-------------------
    //摄像头预览页面
    QObject::connect(&camera,SIGNAL(showMenu()),&tbwindows,SLOT(tipsUpdate()));
    //菜单页面
    QObject::connect(&menu,SIGNAL(showMenu()),&tbwindows,SLOT(tipsUpdate()));
    //多媒体库
    QObject::connect(&dbwindow,SIGNAL(showMenu()),&tbwindows,SLOT(tipsUpdate()));
    //设置页面
    QObject::connect(&setting,SIGNAL(showMenu()),&tbwindows,SLOT(tipsUpdate()));
    //视频播放页面
    QObject::connect(&videoviewer,SIGNAL(showMenu()),&tbwindows,SLOT(tipsUpdate()));
    //图片浏览页面页面
    QObject::connect(&singlephoto,SIGNAL(showMenu()),&tbwindows,SLOT(tipsUpdate()));
    //时间设置页面
    QObject::connect(&timesetting,SIGNAL(showMenu()),&tbwindows,SLOT(tipsUpdate()));
    //系统信息页面
    QObject::connect(&systeminfo,SIGNAL(showMenu()),&tbwindows,SLOT(tipsUpdate()));
    return app.exec();
};
