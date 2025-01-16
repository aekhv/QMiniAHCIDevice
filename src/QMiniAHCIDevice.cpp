/****************************************************************************
**
** This file is part of the QMiniAHCIDevice library.
** Copyright (C) 2025 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#include "QMiniAHCIDevice.h"
#include <sys/ioctl.h>  // ioctl()

QMiniAHCIDevice::QMiniAHCIDevice()
{

}

QStringList QMiniAHCIDevice::availableDevices()
{
    return QMiniPCIDevice::availableDevices("miniahci*");
}

QVector<QMiniAHCIPortNumber> QMiniAHCIDevice::availablePorts()
{
    ahci_controller_info_t info;
    memset(&info, 0, sizeof(info));

    int err = ioctl(fd(), AHCI_IOCTL_GET_CONTROLLER_INFO, &info);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else
        setLastError(QMiniPCIError::NoError);

    QVector<QMiniAHCIPortNumber> ports;
    for (uint32_t i = 0; i < 32; i++) {
        if (info.pi & 1)
            ports.append(QMiniAHCIPortNumber(i));
        info.pi >>= 1;
    }
    return ports;
}

QMiniAHCIPortStatus QMiniAHCIDevice::portStatus()
{
    ahci_port_status_t status;
    memset(&status, 0, sizeof(status));

    status.port = m_port.number();

    int err = ioctl(fd(), AHCI_IOCTL_GET_PORT_STATUS, &status);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else
        setLastError(QMiniPCIError::NoError);

    return QMiniAHCIPortStatus(status);
}

QMiniAHCIDeviceID QMiniAHCIDevice::id()
{
    ata_identify_device_data_t id;
    memset(&id, 0, sizeof(id));

    ahci_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));

    packet.port = m_port.number();
    packet.ata.command = ATA_CMD_IDENTIFY_DEVICE;
    packet.buffer.pointer = (uint8_t *)&id;
    packet.buffer.length = sizeof(id);

    int err = ioctl(fd(), AHCI_IOCTL_RUN_ATA_COMMAND, &packet);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else {
        if (packet.timeout)
            setLastError(QMiniPCIError::DeviceTimeout);
        else
            setLastError(QMiniPCIError::NoError);
    }

    return QMiniAHCIDeviceID(id);
}

bool QMiniAHCIDevice::read(quint64 offset, quint16 count, char *buffer, int length, TransferMode mode)
{
    ahci_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));

    packet.port = m_port.number();
    packet.ata.count[0] = count;
    packet.ata.count[1] = count >> 8;
    packet.ata.lba[0] = offset;
    packet.ata.lba[1] = offset >> 8;
    packet.ata.lba[2] = offset >> 16;
    packet.ata.lba[3] = offset >> 24;
    packet.ata.lba[4] = offset >> 32;
    packet.ata.lba[5] = offset >> 40;
    packet.ata.device = ATA_DEVICE_LBA_MODE;
    packet.ata.command = (mode == DMA) ? ATA_CMD_READ_DMA_EXT : ATA_CMD_READ_SECTORS_EXT;
    packet.buffer.pointer = (uint8_t *)buffer;
    packet.buffer.length = length;
    packet.buffer.write = false;

    int err = ioctl(fd(), AHCI_IOCTL_RUN_ATA_COMMAND, &packet);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else {
        if (packet.timeout)
            setLastError(QMiniPCIError::DeviceTimeout);
        else
            setLastError(QMiniPCIError::NoError);
    }

    return lastError().success();
}

bool QMiniAHCIDevice::write(quint64 offset, quint16 count, char *buffer, int length, TransferMode mode)
{
    ahci_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));

    packet.port = m_port.number();
    packet.ata.count[0] = count;
    packet.ata.count[1] = count >> 8;
    packet.ata.lba[0] = offset;
    packet.ata.lba[1] = offset >> 8;
    packet.ata.lba[2] = offset >> 16;
    packet.ata.lba[3] = offset >> 24;
    packet.ata.lba[4] = offset >> 32;
    packet.ata.lba[5] = offset >> 40;
    packet.ata.device = ATA_DEVICE_LBA_MODE;
    packet.ata.command = (mode == DMA) ? ATA_CMD_WRITE_DMA_EXT : ATA_CMD_WRITE_SECTORS_EXT;
    packet.buffer.pointer = (uint8_t *)buffer;
    packet.buffer.length = length;
    packet.buffer.write = true;

    int err = ioctl(fd(), AHCI_IOCTL_RUN_ATA_COMMAND, &packet);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else {
        if (packet.timeout)
            setLastError(QMiniPCIError::DeviceTimeout);
        else
            setLastError(QMiniPCIError::NoError);
    }

    return lastError().success();
}

void QMiniAHCIDevice::setPortTimeout(int value)
{
    ahci_port_timeout_t timeout;
    timeout.port = m_port.number();
    timeout.value = value;

    int err = ioctl(fd(), AHCI_IOCTL_SET_PORT_TIMOUT, &timeout);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else
        setLastError(QMiniPCIError::NoError);
}

int QMiniAHCIDevice::portTimeout()
{
    ahci_port_timeout_t timeout;
    timeout.port = m_port.number();
    timeout.value = 0;

    int err = ioctl(fd(), AHCI_IOCTL_GET_PORT_TIMOUT, &timeout);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else
        setLastError(QMiniPCIError::NoError);

    return timeout.value;
}

void QMiniAHCIDevice::recalibrate()
{
    ahci_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));

    packet.port = m_port.number();
    packet.ata.command = ATA_CMD_RECALIBRATE;

    int err = ioctl(fd(), AHCI_IOCTL_RUN_ATA_COMMAND, &packet);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else {
        if (packet.timeout)
            setLastError(QMiniPCIError::DeviceTimeout);
        else
            setLastError(QMiniPCIError::NoError);
    }
}

void QMiniAHCIDevice::sleep()
{
    ahci_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));

    packet.port = m_port.number();
    packet.ata.command = ATA_CMD_STANDBY_IMMEDIATE;

    int err = ioctl(fd(), AHCI_IOCTL_RUN_ATA_COMMAND, &packet);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else {
        if (packet.timeout)
            setLastError(QMiniPCIError::DeviceTimeout);
        else
            setLastError(QMiniPCIError::NoError);
    }
}

void QMiniAHCIDevice::softwareReset()
{
    ahci_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));

    packet.port = m_port.number();

    int err = ioctl(fd(), AHCI_IOCTL_PORT_SOFTWARE_RESET, &packet);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else {
        if (packet.timeout)
            setLastError(QMiniPCIError::DeviceTimeout);
        else
            setLastError(QMiniPCIError::NoError);
    }
}

void QMiniAHCIDevice::hardwareReset()
{
    ahci_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));

    packet.port = m_port.number();

    int err = ioctl(fd(), AHCI_IOCTL_PORT_HARDWARE_RESET, &packet);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else
        setLastError(QMiniPCIError::NoError);
}

bool QMiniAHCIDevice::isSMARTStatusBad()
{
    ahci_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));

    packet.port = m_port.number();
    packet.ata.features[0] = ATA_FEATURE_SMART_RETURN_STATUS;
    packet.ata.lba[1] = ATA_SMART_LBA1_SIGNATURE;
    packet.ata.lba[2] = ATA_SMART_LBA2_SIGNATURE;
    packet.ata.command = ATA_CMD_SMART;

    int err = ioctl(fd(), AHCI_IOCTL_RUN_ATA_COMMAND, &packet);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else {
        if (packet.timeout)
            setLastError(QMiniPCIError::DeviceTimeout);
        else
            setLastError(QMiniPCIError::NoError);
    }

    if (!lastError().success())
        return false;

    ahci_port_status_t status;
    memset(&status, 0, sizeof(status));

    status.port = m_port.number();

    err = ioctl(fd(), AHCI_IOCTL_GET_PORT_STATUS, &status);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else
        setLastError(QMiniPCIError::NoError);

    if (!lastError().success())
        return false;

    if ((status.ata.lba[1] != ATA_SMART_LBA1_SIGNATURE)
            && (status.ata.lba[2] != ATA_SMART_LBA2_SIGNATURE))
        return true;
    else
        return false;
}

QVector<QMiniAHCISMARTAttribute> QMiniAHCIDevice::getSMARTAttributes()
{
    ahci_command_packet_t packet;
    memset(&packet, 0, sizeof(packet));

    ata_smart_data_t data;
    memset(&data, 0, sizeof(data));

    packet.port = m_port.number();
    packet.ata.features[0] = ATA_FEATURE_SMART_READ_DATA;
    packet.ata.lba[1] = ATA_SMART_LBA1_SIGNATURE;
    packet.ata.lba[2] = ATA_SMART_LBA2_SIGNATURE;
    packet.ata.command = ATA_CMD_SMART;
    packet.buffer.pointer = (uint8_t *)&data;
    packet.buffer.length = sizeof(data);

    int err = ioctl(fd(), AHCI_IOCTL_RUN_ATA_COMMAND, &packet);
    if (err < 0)
        setLastError(QMiniPCIError::DeviceIoctlError);
    else {
        if (packet.timeout)
            setLastError(QMiniPCIError::DeviceTimeout);
        else
            setLastError(QMiniPCIError::NoError);
    }

    return QMiniAHCISMARTAttribute::fromRawData(data);
}
