/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#include "QMiniAHCISMARTAttribute.h"

QMiniAHCISMARTAttribute::QMiniAHCISMARTAttribute()
    : m_id(0)
{

}

QMiniAHCISMARTAttribute::QMiniAHCISMARTAttribute(const ata_smart_attribute_t &a)
{
    m_id = a.id;
    for (int i = 0; i < 7; i++)
        m_rawData.append(a.raw[i]);
}

QVector<QMiniAHCISMARTAttribute> QMiniAHCISMARTAttribute::fromRawData(const ata_smart_data_t &data)
{
    QVector<QMiniAHCISMARTAttribute> list;
    for (int i = 0; i < 30; i++) {
        ata_smart_attribute_t a = data.attribute[i];
        if (a.id == 0)
            continue;
        QMiniAHCISMARTAttribute attribute = QMiniAHCISMARTAttribute(a);
        list.append(attribute);
    }
    return list;
}

QString QMiniAHCISMARTAttribute::description() const
{
    switch (m_id) {
    case 0x01:
        return "Read Error Rate";
    case 0x03:
        return "Spin-Up Time";
    case 0x04:
        return "Start/Stop Count";
    case 0x05:
        return "Reallocated Sectors Count";
    case 0x07:
        return "Seek Error Rate";
    case 0x09:
        return "Power-On Hours";
    case 0x0A:
        return "Spin Retry Count";
    case 0x0B:
        return "Recalibration Retries";
    case 0x0C:
        return "Power Cycle Count";
    case 0xB8:
        return "End-to-End Error";
    case 0xBB:
        return "Reported Uncorrectable Errors";
    case 0xBC:
        return "Command Timeout";
    case 0xBD:
        return "High Fly Writes";
    case 0xBE:
        return "Airflow Temperature";
    case 0xBF:
        return "G-Sense Error Rate";
    case 0xC0:
        return "Power-Off Retract Count";
    case 0xC1:
        return "Load/Unload Cycle Count";
    case 0xC2:
        return "Device Temperature";
    case 0xC3:
        return "Hardware ECC Recovered";
    case 0xC4:
        return "Reallocation Event Count";
    case 0xC5:
        return "Pending Sectors Count";
    case 0xC6:
        return "Uncorrectable Sectors Count";
    case 0xC7:
        return "UltraDMA CRC Error Count";
    case 0xC8:
        return "Write Error Rate";
    case 0xF0:
        return "Head Flying Hours";
    case 0xF1:
        return "Total Host Writes";
    case 0xF2:
        return "Total Host Reads";
    default:
        return "Unknown";
    }
}

quint32 QMiniAHCISMARTAttribute::rawValue() const
{
    const quint16 *u16 = (quint16 *)m_rawData.data();
    const quint32 *u32 = (quint32 *)m_rawData.data();

    switch (m_id) {
    case 0xBE:
    case 0xC2:
        return *u16;
    default:
        return *u32;
    }
}
