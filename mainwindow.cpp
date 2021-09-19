#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QVariant>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>




#define SPEED 20

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnScan_clicked()
{
    ui->txtOutputWindow->setText("");
    ui->txtOutputWindow->setReadOnly(true);
    QString ip_address = ui ->txtIp->text();
    QString startPort = ui ->txtStartPort->text();
    quint16 portStart = startPort.toUShort();
    QString endPort = ui ->txtEndPort->text();
    quint16 portEnd = endPort.toUShort();
    qInfo()<<ip_address;
    QTcpSocket socket;

    if(portStart>0 && portStart<portEnd)
    {
        for(quint16 i = portStart; i<portEnd; i++)
        {
            socket.connectToHost(ip_address,i);
            QString openPort = QString::number(i);
            QString ip_info = socket.peerName();
            if(socket.waitForConnected(SPEED))
            { 
                ui->txtOutputWindow->append("IP Address: " + ip_info + ", Port opened: " + openPort + ", Timeout: " + QString::number(SPEED) + " ms");
                socket.disconnectFromHost();
            }
            ui->txtOutputWindow->append("IP Address: " + ip_info + ", Port closed: "+ openPort + ", Timeout: " + QString::number(SPEED) + " ms");
            qInfo()<<"Scan has been complited sucesfully";
        }
    }else
    {
        QMessageBox::critical(this,"Incorrect Data", "IncorrectInfo");
    }

}


void MainWindow::on_btnScanOpened_clicked()
{
    ui->txtOutputWindow->setText("");
    ui->txtOutputWindow->setReadOnly(true);
    QString ip_address = ui ->txtIp->text();
    QString startPort = ui ->txtStartPort->text();
    quint16 portStart = startPort.toUShort();
    QString endPort = ui ->txtEndPort->text();
    quint16 portEnd = endPort.toUShort();
    qInfo()<<ip_address;
    QTcpSocket socket;

    if(portStart>0 && portStart<portEnd)
    {
        for(quint16 i = portStart; i<portEnd; i++)
        {
            socket.connectToHost(ip_address,i);
            QString openPort = QString::number(i);
            QString ip_info = socket.peerName();
            if(socket.waitForConnected(SPEED))
            {
                socket.disconnectFromHost();
            }
            else{
            ui->txtOutputWindow->append("IP Address: " + ip_info + ", Port: " + openPort + " is available" + ", Timeout: " + QString::number(SPEED) + " ms");
            qInfo()<<"Scan has been complited sucesfully";
            }
        }
    }else
    {
        QMessageBox::critical(this,"Incorrect Data", "IncorrectInfo");
    }


}


void MainWindow::on_btnScanClosed_clicked()
{
    ui->txtOutputWindow->setText("");
    ui->txtOutputWindow->setReadOnly(true);
    QString ip_address = ui ->txtIp->text();
    QString startPort = ui ->txtStartPort->text();
    quint16 portStart = startPort.toUShort();
    QString endPort = ui ->txtEndPort->text();
    quint16 portEnd = endPort.toUShort();
    qInfo()<<ip_address;
    QTcpSocket socket;


    if(portStart>0 && portStart<portEnd)
    {
        for(quint16 i = portStart; i<portEnd; i++)
        {
            socket.connectToHost(ip_address,i);
            QString openPort = QString::number(i);
            QString ip_info = socket.peerName();
            if(socket.waitForConnected(SPEED))
            {
                ui->txtOutputWindow->append("IP Address: " + ip_info + ", Port: " + openPort + " is occupied" + ", Timeout: " + QString::number(SPEED) + " ms");
                socket.disconnectFromHost();

            }
            qInfo()<<"Scan has been complited sucesfully";
        }
    }else
    {
        QMessageBox::critical(this,"Incorrect Data", "IncorrectInfo");
    }


}

int MainWindow::CalculateTimeout(int startPort, int endPort)
{
    return ((endPort - startPort) / 2);
}

void MainWindow::on_btnSave_clicked()
{
    QDateTime date;
    QString nameFile = QFileDialog::getSaveFileName(this, tr("Save to .txt"), "",
                                                        tr("TXT(.txt);; RTF(.rtf);; DOC(*.doc)"));
        if (nameFile != "") {
                QFile file(nameFile);

                if (file.open(QIODevice::ReadWrite)) {
                 QTextStream stream(&file);

                    stream << "Skan: " + date.currentDateTime().toString("hh:mm dd.MM.yyyy") << "\n" << ui->txtOutputWindow->toPlainText() ;
                    file.flush();
                    file.close();
                }
                else {
                    QMessageBox::critical(this, tr("Error"), tr("Can't save file"));
                    return;
                }
            }
}
