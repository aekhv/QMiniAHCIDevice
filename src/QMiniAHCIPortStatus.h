/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMINIAHCIPORTSTATUS_H
#define QMINIAHCIPORTSTATUS_H

#include "QMiniAHCIPortLinkStatus.h"
#include "QMiniAHCIPortATAStatus.h"

class QMiniAHCIPortStatus
{
public:
    QMiniAHCIPortStatus();
    QMiniAHCIPortStatus(const ahci_port_status_t &status);

    QMiniAHCIPortLinkStatus link() const { return m_link; }
    QMiniAHCIPortATAStatus ata() const { return m_ata; }

private:
    QMiniAHCIPortLinkStatus m_link;
    QMiniAHCIPortATAStatus m_ata;
};

#endif // QMINIAHCIPORTSTATUS_H
