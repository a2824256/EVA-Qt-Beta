#ifndef COMMON_H
#define COMMON_H

#include <string.h>
#include <QtWidgets>
class Common
{
public:
    Common();
    static QString _medicalNumber;
    static QString _tips;
};

void Qlog(QString log);
#endif // COMMON_H
