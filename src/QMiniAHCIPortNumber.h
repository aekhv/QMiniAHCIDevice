/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMINIAHCIPORTNUMBER_H
#define QMINIAHCIPORTNUMBER_H

#include <QtCore>

class QMiniAHCIPortNumber
{
public:
    QMiniAHCIPortNumber(int number = 0);
    int number() const { return m_number; }
    QString toString() const;

private:
    int m_number;
};

#endif // QMINIAHCIPORTNUMBER_H
