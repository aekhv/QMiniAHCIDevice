/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMINIAHCISMARTATTRIBUTE_H
#define QMINIAHCISMARTATTRIBUTE_H

#include <QtCore>
#include "QMiniAHCICommon.h"

class QMiniAHCISMARTAttribute
{
public:
    QMiniAHCISMARTAttribute();
    QMiniAHCISMARTAttribute(const ata_smart_attribute_t &a);

    static QVector<QMiniAHCISMARTAttribute> fromRawData(const ata_smart_data_t &data);

    int id() const { return m_id; }
    QByteArray rawData() const { return m_rawData; }
    QString description() const;
    quint32 rawValue() const;

private:
    int m_id;
    QByteArray m_rawData;
};

#endif // QMINIAHCISMARTATTRIBUTE_H
