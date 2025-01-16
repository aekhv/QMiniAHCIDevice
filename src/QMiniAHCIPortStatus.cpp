/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#include "QMiniAHCIPortStatus.h"

QMiniAHCIPortStatus::QMiniAHCIPortStatus()
{

}

QMiniAHCIPortStatus::QMiniAHCIPortStatus(const ahci_port_status_t &status)
{
    m_link = QMiniAHCIPortLinkStatus(status.link);
    m_ata = QMiniAHCIPortATAStatus(status.ata);
}
