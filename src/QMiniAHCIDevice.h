/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMINIAHCIDEVICE_H
#define QMINIAHCIDEVICE_H

#include <QMiniPCIDevice.h>
#include "QMiniAHCIPortNumber.h"
#include "QMiniAHCIPortStatus.h"
#include "QMiniAHCIDeviceID.h"
#include "QMiniAHCISMARTAttribute.h"

class QMiniAHCIDevice : public QMiniPCIDevice
{
public:
    enum TransferMode {
        PIO,
        DMA
    };

    QMiniAHCIDevice();

    static QStringList availableDevices();

    QVector<QMiniAHCIPortNumber> availablePorts();
    void setCurrentPort(const QMiniAHCIPortNumber &port) { m_port = port; }
    QMiniAHCIPortNumber currentPort() const { return m_port; }
    QMiniAHCIPortStatus portStatus();
    QMiniAHCIDeviceID id();

    bool read(quint64 offset, quint16 count, char *buffer, int length, TransferMode mode = DMA);
    bool write(quint64 offset, quint16 count, char *buffer, int length, TransferMode mode = DMA);

    void setPortTimeout(int value);
    int portTimeout();

    void recalibrate();
    void sleep();

    void softwareReset(); /* Do not use this. It works well, but when BSY=0 and ERR=0 only. It's useless in real life. */
    void hardwareReset(); /* Always use this */

    bool isSMARTStatusBad();
    QVector<QMiniAHCISMARTAttribute> getSMARTAttributes();

private:
    QMiniAHCIPortNumber m_port;
};

#endif // QMINIAHCIDEVICE_H
