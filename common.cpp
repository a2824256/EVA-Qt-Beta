#include "common.h"
//病历号
QString Common::_medicalNumber = "";
//头部提示
QString Common::_tips = "";
//系统平台
QString Common::_OS = "mac";
//是否打印log
bool Common::_isLog = true;
//本机多媒体库路径
QString Common::_multimediaFolderPath = "";
//型号：VL3:基本型（拍照录像）VL3-PRO:专业型（全功能） VL3-SE:定制型(只含预览)
QString Common::_model = "VL3-PRO";
QString Common::_softwareVersion = "1.0 beta";
QString Common::_hardwareVersion = "1.0";
//中文:CN 英文:EN, 这里设置系统启动语言
QString Common::_language = "CN";
//序列号
QString Common::_serialNumber = "zx202002000001";
//批号
QString Common::_batchNumber = "20200808";
//厂家维护模式密码
QString Common::_password = "997995";

Common::Common()
{

}

void Qlog(QString log){
    if(Common::_isLog){
        qDebug()<<log<<endl;
    }
}
void updatePath(){
    QString aFile = QDir::currentPath();
    QDir localPath(aFile);
    if(Common::_OS == "mac"){
        localPath.cdUp();
        localPath.cdUp();
        localPath.cdUp();
        localPath.setPath(localPath.path()+"/multimedia");
        if (!localPath.exists()) {
//            qDebug()<<localPath.path()<<endl;
            localPath.mkpath(localPath.path());
        }
    }else if(Common::_OS == "linux"){

    }
    Common::_multimediaFolderPath = localPath.path();
//    qDebug()<<localPath.path()<<endl;
}
