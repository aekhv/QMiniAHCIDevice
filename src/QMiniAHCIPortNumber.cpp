/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#include "QMiniAHCIPortNumber.h"

QMiniAHCIPortNumber::QMiniAHCIPortNumber(int number)
    : m_number(number)
{

}

QString QMiniAHCIPortNumber::toString() const
{
    return QString("Port%1").arg(m_number);
}
