/*
 *
 * MashBerry Homebrewing-controller
 *
 * Copyright (C) 2013 Sebastian Duell
 * <mail@sebastian-duell.de>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 3. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <QDir>

#include "qtempsensords18b20.h"

#ifndef Q_OS_WIN
#include <linux/i2c-dev.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#endif

#define SENSOR_I2C_ADDR 0x78

QTempSensorDS18B20::QTempSensorDS18B20(QObject *parent) :
    QTempSensor(parent)
{
    m_fd = NULL;
    m_fname = NULL;
    m_lastTemp = 25.0;
}

QTempSensorDS18B20::QTempSensorDS18B20(QString filename) :
    QTempSensor()
{
    m_fname = new char[filename.length() + 1];
    strcpy(m_fname, filename.toStdString().c_str());
}

QTempSensorDS18B20::~QTempSensorDS18B20()
{
    if(m_fname != NULL)
        delete m_fname;
}

int QTempSensorDS18B20::Open()
{
    if(m_fname != NULL)
    {
        return 0;
    }

    QStringList list = GetSensorPaths();

    if(list.isEmpty())
    {
        printf("couldn't find ds18b20 device\n");
        return 1;
    }
    else
    {
        QString fname = list.first();
        m_fname = new char[fname.length() + 1];
        strcpy(m_fname, fname.toStdString().c_str());
        return 0;
    }
}

QList<QTempSensorDS18B20*> QTempSensorDS18B20::GetAllSensors()
{
    QList<QTempSensorDS18B20*> list;

    foreach(QString path, GetSensorPaths())
    {
        list.append(new QTempSensorDS18B20(path));
    }

    return list;
}

QStringList QTempSensorDS18B20::GetSensorPaths()
{
    QStringList list;
    QString fname;

#ifndef Q_OS_WIN
    QDir dir("/sys/bus/w1/devices/");
    QStringList dirlist;
    int i,cnt;

    dirlist = dir.entryList(QDir::Dirs|QDir::System|QDir::Files|QDir::NoDotAndDotDot);

    cnt = dirlist.count();
    for(i=0;i<cnt;i++)
    {
        fname = dirlist[i];
        if(fname != "w1_bus_master1" && fname.contains("-"))
        {
            list.append(dir.absoluteFilePath(fname) + "/w1_slave");
        }
    }
#endif

    return list;
}

double QTempSensorDS18B20::ReadTemp()
{
#ifndef Q_OS_WIN
    double temp = 0;
    unsigned int i=0;

    if(m_fname)
    {
        m_fd = fopen(m_fname, "rb");
        if(m_fd > 0)
        {
            fscanf(m_fd, "%*[^t]t=%u", &i);
            fclose(m_fd);
        }
    }
    i = i/100;
    i = i*100;
    temp = (double)(i/1000.0);
    if(temp < 0 || temp > 250.0)
        temp = m_lastTemp;
    else
        m_lastTemp = temp;

    return temp;
//    return i/1000.0;
#else
    return 20.0;
#endif
}

int QTempSensorDS18B20::GetSampleTime()
{
    return 10;//4;
}
