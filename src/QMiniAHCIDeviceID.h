/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMINIAHCIDEVICEID_H
#define QMINIAHCIDEVICEID_H

#include <QtCore>
#include "QMiniAHCICommon.h"

class QMiniAHCIDeviceID
{
public:
    QMiniAHCIDeviceID();
    QMiniAHCIDeviceID(const ata_identify_device_data_t &id);

    QString modelName() const { return m_mdl; }
    QString firmwareRevision() const { return m_fw; }
    QString serialNumber() const { return m_sn; }
    quint64 sectorCount() const { return m_sc; }
    quint16 sectorSize() const { return m_ss; }
    qint64 totalCapacity() const { return m_sc * m_ss; }
    QString friendlyName() const;

private:
    QString m_mdl;
    QString m_fw;
    QString m_sn;
    qint64 m_sc;
    quint16 m_ss;
};

#endif // QMINIAHCIDEVICEID_H
