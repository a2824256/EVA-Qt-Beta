#include "common.h"

QString Common::_medicalNumber = "";
QString Common::_tips = "";

Common::Common()
{

}

void Qlog(QString log){
    qDebug()<<log<<endl;
}
