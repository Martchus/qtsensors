/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#include <QDir>
#include <QLibraryInfo>

#include "qsensorgesturerecognizer.h"
#include "qsensorgesturemanagerprivate_p.h"
#include "qsensorgestureplugininterface.h"
#include "qmobilitypluginsearch.h"

QT_BEGIN_NAMESPACE

QSensorGestureManagerPrivate::QSensorGestureManagerPrivate(QObject *parent) :
    QObject(parent)
{
    loadPlugins();
}

QSensorGestureManagerPrivate::~QSensorGestureManagerPrivate()
{
    qDeleteAll(registeredSensorGestures);
    qDeleteAll(plugins);
}


 void QSensorGestureManagerPrivate::initPlugin(QObject *plugin)
{
    if (QSensorGesturePluginInterface *pInterface
            = qobject_cast<QSensorGesturePluginInterface *>(plugin)) {

        Q_FOREACH (const QString &id, pInterface->supportedIds()) {

            if (!knownIds.contains(id))
                knownIds.append(id);
            else
                qWarning() << id <<"from the plugin"
                           << pInterface->name()
                           << "is already known.";

        }
        plugins << plugin;
    }
}

/*!
  Internal
  Loads the sensorgesture plugins.
  */
void QSensorGestureManagerPrivate::loadPlugins()
{
    // Qt-style static plugins
    Q_FOREACH (QObject *plugin, QPluginLoader::staticInstances()) {
        initPlugin(plugin);
    }

    QStringList gestureplugins = mobilityPlugins(QLatin1String("sensorgestures"));
    for (int i = 0; i < gestureplugins.count(); i++) {

        QPluginLoader *loader = new QPluginLoader(gestureplugins.at(i), this);

        QObject *plugin = loader->instance();
        if (plugin) {
            initPlugin(plugin);
        }
    }
}


/*!
  Internal
  creates the requested  recognizer.
  */

bool QSensorGestureManagerPrivate::loadRecognizer(const QString &recognizerId)
{
    for (int i= 0; i < plugins.count(); i++) {

        if (QSensorGesturePluginInterface *pInterface
                = qobject_cast<QSensorGesturePluginInterface *>(plugins.at(i))) {
            if (pInterface->supportedIds().contains(recognizerId)) {
                if (!registeredSensorGestures.contains(recognizerId)) {
                    //create these recognizers
                    QList <QSensorGestureRecognizer *> recognizers = pInterface->createRecognizers();

                    Q_FOREACH (QSensorGestureRecognizer *recognizer, recognizers) {

                        if (registeredSensorGestures.contains(recognizer->id())) {
                           qWarning() << "Ignoring recognizer " << recognizer->id() << "from plugin" << pInterface->name() << "because it is already registered";
                            delete recognizer;
                        } else {
                            registeredSensorGestures.insert(recognizer->id(),recognizer);
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}

bool QSensorGestureManagerPrivate::registerSensorGestureRecognizer(QSensorGestureRecognizer *recognizer)
{
    if (!knownIds.contains(recognizer->id())) {
        knownIds.append(recognizer->id());
        Q_ASSERT (!registeredSensorGestures.contains(recognizer->id()));
        recognizer->setParent(0);
        registeredSensorGestures.insert(recognizer->id(),recognizer);

        return true;
    }

    qWarning() << recognizer->id() << "is already known";

    return false;
}

QSensorGestureRecognizer *QSensorGestureManagerPrivate::sensorGestureRecognizer(const QString &id)
{
    QSensorGestureRecognizer *recognizer = 0;

    if (loadRecognizer(id)) {
        recognizer= registeredSensorGestures.value(id);
    }

    return recognizer;
}

QStringList QSensorGestureManagerPrivate::gestureIds()
{
    return knownIds;
}


QT_END_NAMESPACE
