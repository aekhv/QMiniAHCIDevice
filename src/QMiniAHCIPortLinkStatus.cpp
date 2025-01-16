/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#include "QMiniAHCIPortLinkStatus.h"

QMiniAHCIPortLinkStatus::QMiniAHCIPortLinkStatus()
    : m_sig(0),
      m_det(0),
      m_spd(0)
{

}

QMiniAHCIPortLinkStatus::QMiniAHCIPortLinkStatus(const ahci_port_link_status_t &link)
{
    m_sig = link.sig;
    m_det = link.det;
    m_spd = link.spd;
}
