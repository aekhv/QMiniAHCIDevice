#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void refresh();
    void enumeratePorts();
    void updateStatus();
    void getID();
    void recalibrate();
    void sleep();
    void softReset();
    void hardReset();
    void getSMART();
    void readTest();

private:
    Ui::MainWindow *ui;
    QTimer timer;

    QString ataStatusToString(quint8 status);
    QString ataErrorToString(quint8 error);
};
#endif // MAINWINDOW_H
