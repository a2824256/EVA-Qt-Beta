#ifndef COMMON_H
#define COMMON_H

#include <string.h>
#include <QtWidgets>
//公共设置类库
class Common
{
public:
    Common();
    static QString _medicalNumber;
    static QString _tips;
    static QString _OS;
    static bool _isLog;
    static QString _multimediaFolderPath;
    static QString _model;
    static QString _softwareVersion;
    static QString _hardwareVersion;
    static QString _language;
    static QString _serialNumber;
    static QString _batchNumber;
    static QString _password;

};

void Qlog(QString log);
void updatePath();
#endif // COMMON_H
