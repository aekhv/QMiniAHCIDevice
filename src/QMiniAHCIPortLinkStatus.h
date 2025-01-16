/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMINIAHCIPORTLINKSTATUS_H
#define QMINIAHCIPORTLINKSTATUS_H

#include <QtCore>
#include "../../miniahci/ioctl.h"
#include "QMiniAHCICommon.h"

class QMiniAHCIPortLinkStatus
{
public:
    QMiniAHCIPortLinkStatus();
    QMiniAHCIPortLinkStatus(const ahci_port_link_status_t &link);

    quint32 signatureIsValid() const { return m_sig == SATA_DEVICE_SIGNATURE; }
    bool deviceDetected() const { return m_det == SATA_DEVICE_DETECTED; }
    int speed() const { return m_spd; }

private:
    quint32 m_sig;
    int m_det, m_spd;
};

#endif // QMINIAHCIPORTLINKSTATUS_H
