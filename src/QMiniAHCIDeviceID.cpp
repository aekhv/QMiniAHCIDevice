/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#include "QMiniAHCIDeviceID.h"

QMiniAHCIDeviceID::QMiniAHCIDeviceID()
    : m_sc(0),
      m_ss(512)
{

}

QMiniAHCIDeviceID::QMiniAHCIDeviceID(const ata_identify_device_data_t &id)
{
    QString mdl;
    for (uint8_t i = 0; i < sizeof(id.model); i += 2)
    {
        mdl.append(id.model[i + 1]);
        mdl.append(id.model[i]);
    }
    m_mdl = mdl.trimmed();

    QString fw;
    for (uint8_t i = 0; i < sizeof(id.firmware); i += 2)
    {
        fw.append(id.firmware[i + 1]);
        fw.append(id.firmware[i]);
    }
    m_fw = fw.trimmed();

    QString sn;
    for (uint8_t i = 0; i < sizeof(id.serial_number); i += 2)
    {
        sn.append(id.serial_number[i + 1]);
        sn.append(id.serial_number[i]);
    }
    m_sn = sn.trimmed();

    m_sc = id.user_capacity;

    m_ss = 512;
    if ((id.phy_ss_shall_be_one == 1) && (id.phy_ss_shall_be_zero == 0))
        if (id.device_ls_longer_than_256_words)
            m_ss = 2 * id.words_per_logical_sector;
}

QString QMiniAHCIDeviceID::friendlyName() const
{
    QString s = QString("%1 %2 %3")
            .arg(m_mdl)
            .arg(m_fw)
            .arg(m_sn);

    return s.trimmed().isEmpty() ? "Unknown device" : s.trimmed();
}
