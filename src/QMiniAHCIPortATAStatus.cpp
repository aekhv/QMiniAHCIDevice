/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#include "QMiniAHCIPortATAStatus.h"

QMiniAHCIPortATAStatus::QMiniAHCIPortATAStatus()
    : m_status(0),
      m_error(0),
      m_lba(0)
{

}

QMiniAHCIPortATAStatus::QMiniAHCIPortATAStatus(const ahci_port_ata_status_t &ata)
{
    m_status = ata.status;
    m_error = ata.error;

    m_lba = ata.lba[5];
    for (int i = 4; i >= 0; i--) {
        m_lba <<= 8;
        m_lba |= ata.lba[i];
    }
}
