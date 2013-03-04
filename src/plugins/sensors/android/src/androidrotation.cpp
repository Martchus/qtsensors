/****************************************************************************
**
** Copyright (C) 2013 BogDan Vatra <bogdan@kde.org>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "androidrotation.h"
#include <math.h>

AndroidRotation::AndroidRotation(AndroidSensors::AndroidSensorType type, QSensor *sensor)
    : AndroidCommonSensor<QRotationReading>(type, sensor)
{}

void AndroidRotation::onAccuracyChanged(jint accuracy)
{
    Q_UNUSED(accuracy)
}

void AndroidRotation::onSensorChanged(jlong timestamp, const jfloat *values, uint size)
{
    if (size < 3)
        return;
    m_reader.setTimestamp(timestamp);

    float rz = -values[0]*180/M_PI;
    float rx = -values[1]*180/M_PI;
    float ry = values[2]*180/M_PI;
    m_reader.setFromEuler(rx, ry, rz);
    newReadingAvailable();
}
