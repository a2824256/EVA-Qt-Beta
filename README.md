# EVA-Qt-Beta
内窥镜小主机送检版本-qt版本

## 开发环境
- MacOS 10.14.6 & Ubuntu 16.04
- Qt 5.12.2

## 目标环境
- 系统： Linux + Qt 5.12.2
- 桌面系统：Qt Launcher
- 主控芯片： 瑞芯微PX30

## 功能
- 拍照 + logo与时间水印 (v)
- 录像 (v)
- 照片浏览 (v)
- 录像回放 (v)
- 设置系统时间 (x)
- 查看软硬件版本 (v)
- 开关声音 (x)
- 后台线程通过串口与ADC获得电池电量 (x)

## 界面
- 拍照&录像界面 (v)
- 菜单页面 (v)
- 图库界面（图片列表） (v)
- 图片浏览界面 (v)
- 视频库界面（视频列表） (v)
- 视频浏览界面 (v)
- 设置页面 (v)
- 系统信息页面 (v)
- 系统时间设置页面 (v)

## 更新日志
+ 2020/01/16 
 图片与视频功能合并为文件浏览,自动识别文件夹、视频、图片并且点击完成对应的操作
+ 2020/01/18 
 抽取顶部栏独立为一个永久置顶的窗口,方便后面做电池电量显示


## TODO List
- 后台线程通过串口与ADC获得电池电量
- 调用linux指令更新系统时间
- 整合ffmpeg边录边压制视频音频

## 截图
- 拍照&录像 <br/>
<img src="https://github.com/a2824256/EVA-Qt-Beta/blob/master/screenshots/4851578384434_.pic.jpg" width="716" height="537">

- 图片列表(点击放大) <br/>
<img src="https://github.com/a2824256/EVA-Qt-Beta/blob/master/screenshots/4861578385247_.pic.jpg" width="716" height="537">

- 调整系统时间 <br/>
<img src="https://github.com/a2824256/EVA-Qt-Beta/blob/master/screenshots/4871578385280_.pic.jpg" width="716" height="537">

- 图片浏览+水印展示 <br/>
<img src="https://github.com/a2824256/EVA-Qt-Beta/blob/master/screenshots/5121578991713_.pic.jpg" width="716" height="537">

- 视频列表（使用opencv读取每个视频第一帧）
<img src="https://github.com/a2824256/EVA-Qt-Beta/blob/master/screenshots/5131578992616_.pic.jpg" width="716" height="537">
