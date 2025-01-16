/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMINIAHCIPORTATASTATUS_H
#define QMINIAHCIPORTATASTATUS_H

#include <QtCore>
#include "../../miniahci/ioctl.h"

class QMiniAHCIPortATAStatus
{
public:
    QMiniAHCIPortATAStatus();
    QMiniAHCIPortATAStatus(const ahci_port_ata_status_t &ata);

    quint8 statusRegister() const { return m_status; }
    quint8 errorRegister() const { return m_error; }
    quint64 lastErrorLBA() const { return m_lba; }

    bool success() const { return (m_status & 0x81) == 0; }
    bool busyBitIsSet() const { return (m_status & 0x80) == 0x80; }
    bool errorBitIsSet() const { return (m_status & 0x01) == 0x01; }

private:
    quint8 m_status, m_error;
    quint64 m_lba;
};

#endif // QMINIAHCIPORTATASTATUS_H
