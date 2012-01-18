/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSENSORDATA_SIMULATOR_P_H
#define QSENSORDATA_SIMULATOR_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/QMetaType>
#include <QtCore/QDateTime>

namespace QtMobility {

enum SimulatorLightLevel {
    Undefined = 0,
    Dark,
    Twilight,
    Light,
    Bright,
    Sunny
};

struct QAmbientLightReadingData
{
    SimulatorLightLevel lightLevel;
    QDateTime timestamp;
};

struct QLightReadingData
{
    double lux;
    QDateTime timestamp;
};

struct QAccelerometerReadingData
{
    double x;
    double y;
    double z;
    QDateTime timestamp;
};

struct QMagnetometerReadingData
{
    double x;
    double y;
    double z;
    double calibrationLevel;
    QDateTime timestamp;
};

struct QCompassReadingData
{
    double azimuth;
    double calibrationLevel;
    QDateTime timestamp;
};

struct QProximityReadingData
{
    bool close;
    QDateTime timestamp;
};

struct QIRProximityReadingData
{
    double irProximity;
    QDateTime timestamp;
};

void qt_registerSensorTypes();

}

Q_DECLARE_METATYPE(QtMobility::QAmbientLightReadingData)
Q_DECLARE_METATYPE(QtMobility::QLightReadingData)
Q_DECLARE_METATYPE(QtMobility::QAccelerometerReadingData)
Q_DECLARE_METATYPE(QtMobility::QMagnetometerReadingData)
Q_DECLARE_METATYPE(QtMobility::QCompassReadingData)
Q_DECLARE_METATYPE(QtMobility::QProximityReadingData)
Q_DECLARE_METATYPE(QtMobility::QIRProximityReadingData)

#endif // QSENSORDATA_SIMULATOR_P_H
