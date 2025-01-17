#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMiniAHCIDevice.h>
#include <QThread>

#define output(s) ui->plainTextEdit->appendPlainText(s)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->refreshButton, &QPushButton::pressed, this, &MainWindow::refresh);
    connect(ui->deviceBox, &QComboBox::currentTextChanged, this, &MainWindow::enumeratePorts);
    connect(&timer, &QTimer::timeout, this, &MainWindow::updateStatus);
    connect(ui->idButton, &QPushButton::pressed, this, &MainWindow::getID);
    connect(ui->recalibrateButton, &QPushButton::pressed, this, &MainWindow::recalibrate);
    connect(ui->sleepButton, &QPushButton::pressed, this, &MainWindow::sleep);
    connect(ui->sResetButton, &QPushButton::pressed, this, &MainWindow::softReset);
    connect(ui->hResetButton, &QPushButton::pressed, this, &MainWindow::hardReset);
    connect(ui->smartButton, &QPushButton::pressed, this, &MainWindow::getSMART);
    connect(ui->readTestButton, &QPushButton::pressed, this, &MainWindow::readTest);

    refresh();

    timer.setInterval(500);
    timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    ui->deviceBox->clear();
    const QStringList devices = QMiniAHCIDevice::availableDevices();
    foreach (const QString dev, devices)
        ui->deviceBox->addItem(dev);
}

void MainWindow::enumeratePorts()
{
    ui->portBox->clear();

    QMiniAHCIDevice ahci;
    const QString dev = ui->deviceBox->currentText();

    if (!ahci.open(dev))
        return;

    QVector<QMiniAHCIPortNumber> ports = ahci.availablePorts();
    foreach(const QMiniAHCIPortNumber p, ports) {
        ui->portBox->addItem(p.toString(), QVariant(p.number()));
    }
}

void MainWindow::updateStatus()
{
    QMiniAHCIDevice ahci;
    const QString dev = ui->deviceBox->currentText();
    const int port = ui->portBox->currentData().toInt();

    if (!ahci.open(dev))
        return;

    ahci.setCurrentPort(QMiniAHCIPortNumber(port));
    QMiniAHCIPortStatus status = ahci.portStatus();

    QString s = ataStatusToString(status.ata().statusRegister());
    QString e = ataErrorToString(status.ata().errorRegister());

    QString phy;
    if (status.link().deviceDetected())
        phy = "[<font color=\"green\">PHY</font>]";
    else
        phy = "[<font color=\"gray\">No link</font>]";

    QString speed;
    switch (status.link().speed()) {
    case 1:
    case 2:
    case 3:
        speed = QString("[<font color=\"green\">SATA-%1</font>]").arg(status.link().speed());
        break;
    default:
        speed = "[<font color=\"gray\">No link</font>]";
    }

    QString str = QString("%1 %2 %3 %4")
            .arg(s).arg(e).arg(phy).arg(speed);

    ui->statusLabel->setText(str);
}

QString MainWindow::ataStatusToString(quint8 status)
{
    const QStringList bits = {"BSY", "DRD", "DWF", "DSC", "DRQ", "CRR", "IDX", "ERR"};
    quint8 n = 0x80;
    QString s;
    for (int i = 0; i < bits.count(); i++) {
        s.append(QString("<font color=\"%1\">%2</font> ")
                    .arg((status & n) ? "blue" : "gray" )
                    .arg(bits.at(i)));
        n >>= 1;
    }
    return QString("[%1]").arg(s.trimmed());
}

QString MainWindow::ataErrorToString(quint8 error)
{
    const QStringList bits = {"BBK", "UNC", "MCD", "INF", "MCR", "ABR", "T0N", "AMN"};
    quint8 n = 0x80;
    QString s;
    for (int i = 0; i < bits.count(); i++) {
        s.append(QString("<font color=\"%1\">%2</font> ")
                    .arg((error & n) ? "red" : "gray" )
                    .arg(bits.at(i)));
        n >>= 1;
    }
    return QString("[%1]").arg(s.trimmed());
}


void MainWindow::getID()
{
    QMiniAHCIDevice ahci;
    const QString dev = ui->deviceBox->currentText();
    const int port = ui->portBox->currentData().toInt();

    output("");

    if (!ahci.open(dev)) {
        output("Device opening error!");
        return;
    }

    output("*** DEVICE ID ***\n");

    ahci.setCurrentPort(QMiniAHCIPortNumber(port));
    QMiniAHCIDeviceID id = ahci.id();

    QMiniPCIError err = ahci.lastError();
    if (!err.success()) {
        output(err.toString());
        return;
    }

    QMiniAHCIPortStatus status = ahci.portStatus();
    if (!status.ata().success()) {
        output("Device busy or error occured!");
        return;
    }

    output(QString("Model name: %1")
           .arg(id.modelName()));
    output(QString("Firmware revision: %1")
           .arg(id.firmwareRevision()));
    output(QString("Serial number: %1")
           .arg(id.serialNumber()));
    output(QString("Capacity: %1 GB")
           .arg(id.totalCapacity() / (1000.0 * 1000.0 * 1000.0), 0, 'f', 1));
    output(QString("Sector size: %1 bytes")
           .arg(id.sectorSize()));
}

void MainWindow::recalibrate()
{
    QMiniAHCIDevice ahci;
    const QString dev = ui->deviceBox->currentText();
    const int port = ui->portBox->currentData().toInt();

    output("");

    if (!ahci.open(dev)) {
        output("Device opening error!");
        return;
    }

    output("*** RECALIBRATE ***");

    ahci.setCurrentPort(QMiniAHCIPortNumber(port));
    ahci.recalibrate();

    QMiniPCIError err = ahci.lastError();
    if (!err.success()) {
        output(err.toString());
        return;
    }

    QMiniAHCIPortStatus status = ahci.portStatus();
    if (!status.ata().success())
        output("Device busy or error occured!");
    else
        output("Ok.");
}

void MainWindow::sleep()
{
    QMiniAHCIDevice ahci;
    const QString dev = ui->deviceBox->currentText();
    const int port = ui->portBox->currentData().toInt();

    output("");

    if (!ahci.open(dev)) {
        output("Device opening error!");
        return;
    }

    output("*** SLEEP ***");

    ahci.setCurrentPort(QMiniAHCIPortNumber(port));
    ahci.sleep();

    QMiniPCIError err = ahci.lastError();
    if (!err.success()) {
        output(err.toString());
        return;
    }

    QMiniAHCIPortStatus status = ahci.portStatus();
    if (!status.ata().success())
        output("Device busy or error occured!");
    else
        output("Ok.");
}

void MainWindow::softReset()
{
    QMiniAHCIDevice ahci;
    const QString dev = ui->deviceBox->currentText();
    const int port = ui->portBox->currentData().toInt();

    output("");

    if (!ahci.open(dev)) {
        output("Device opening error!");
        return;
    }

    output("*** SOFT RESET ***");

    ahci.setCurrentPort(QMiniAHCIPortNumber(port));
    ahci.softwareReset();

    QMiniPCIError err = ahci.lastError();
    if (!err.success()) {
        output(err.toString());
        return;
    }

    QThread::msleep(250);

    QMiniAHCIPortStatus status = ahci.portStatus();
    if (!status.ata().success())
        output("Device busy or error occured!");
    else
        output("Ok.");
}

void MainWindow::hardReset()
{
    QMiniAHCIDevice ahci;
    const QString dev = ui->deviceBox->currentText();
    const int port = ui->portBox->currentData().toInt();

    output("");

    if (!ahci.open(dev)) {
        output("Device opening error!");
        return;
    }

    output("*** HARD RESET ***");

    ahci.setCurrentPort(QMiniAHCIPortNumber(port));
    ahci.hardwareReset();

    QMiniPCIError err = ahci.lastError();
    if (!err.success()) {
        output(err.toString());
        return;
    }

    QThread::msleep(250);

    QMiniAHCIPortStatus status = ahci.portStatus();
    if (!status.ata().success())
        output("Device busy or error occured!");
    else
        output("Ok.");
}

void MainWindow::getSMART()
{
    QMiniAHCIDevice ahci;
    const QString dev = ui->deviceBox->currentText();
    const int port = ui->portBox->currentData().toInt();

    output("");

    if (!ahci.open(dev)) {
        output("Device opening error!");
        return;
    }

    output("*** S.M.A.R.T. ***\n");

    ahci.setCurrentPort(QMiniAHCIPortNumber(port));

    bool bad = ahci.isSMARTStatusBad();

    QMiniPCIError err = ahci.lastError();
    if (!err.success()) {
        output(err.toString());
        return;
    }

    output(QString("S.M.A.R.T. common status: %1\n").arg(bad ? "BAD" : "GOOD"));

    QVector<QMiniAHCISMARTAttribute> attributes = ahci.getSMARTAttributes();

    err = ahci.lastError();
    if (!err.success()) {
        output(err.toString());
        return;
    }

    foreach (const QMiniAHCISMARTAttribute a, attributes) {
        QString hex = QString("%1")
                .arg((quint8)a.rawData().at(0), 2, 16, QChar('0'));
        for (int i = 1; i < 7; i++) {
            QString c = QString("%1")
                    .arg((quint8)a.rawData().at(i), 2, 16, QChar('0'));
            hex = hex + ":" + c;
        }

        QString s = QString("<font color=\"green\">[%1]</font> %2: <font color=\"blue\">%3</font> [%4]")
                .arg(a.id(), 2, 16, QChar('0'))
                .arg(a.description())
                .arg(a.rawValue())
                .arg(hex);
        ui->plainTextEdit->appendHtml(s);
    }
}

void MainWindow::readTest()
{
    QMiniAHCIDevice ahci;
    const QString dev = ui->deviceBox->currentText();
    const int port = ui->portBox->currentData().toInt();

    output("");

    if (!ahci.open(dev)) {
        output("Device opening error!");
        return;
    }

    output("*** READ TEST ***");

    ahci.setCurrentPort(QMiniAHCIPortNumber(port));
    QMiniAHCIDeviceID id = ahci.id();

    QByteArray buffer(262144, 0);

    const quint32 count = buffer.size() / id.sectorSize();
    quint64 offset = 0;

    int t = 5000; // Time for testing in ms
    QTimer timer;
    timer.setSingleShot(true);
    timer.start(t);

    while (timer.remainingTime() > 0) {
        ahci.read(offset, count, buffer.data(), buffer.size());

        // Basic error handling...
        QMiniPCIError error = ahci.lastError();

        if (!error.success()) {
            output(error.toString());
            return;
        }

        QMiniAHCIPortStatus status = ahci.portStatus();

        if (status.ata().busyBitIsSet()) {
            output("Busy bit is set!");
            return;
        }

        if (status.ata().errorBitIsSet()) {
            output(QString("Error bit is set! Last error LBA is %1.")
                   .arg(status.ata().firstErrorLBA()));
            return;
        }

        if (status.link().speed() == 0) {
            output("Communication lost!");
            return;
        }

        offset += count;
    }

    double speed = (offset * id.sectorSize()) / (t * 1000.0);
    output(QString("Average read speed: %1 MB/sec")
           .arg(speed, 0, 'f', 1));
}
