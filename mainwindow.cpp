#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>

#include <QMandala.h>
#include "escparser.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    if(filename.isEmpty())
        return;

    ui->labelErrorsCount->setText(QString("Errors: %1").arg(0));
    ui->labelPacketsCount->setText(QString("Packets: %1").arg(0));

    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    EscParser parser;
    QByteArray data = file.readAll();
    EscParser::DataBuffer dataBuffer;
    std::copy(data.begin(), data.end(), std::back_inserter(dataBuffer));

    var->rec->setRecording(true);
    int errorsCount = 0;
    int packetsCount = 0;
    EscParser::DataBuffer packet;
    while(true)
    {
        auto result = parser.extractData(dataBuffer, packet);
        if(result == EscParser::erDataEnd)
            break;
        else if(result == EscParser::erCrcError || result == EscParser::erUnknownError)
            errorsCount++;
        else if(result == EscParser::erOk)
            packetsCount++;
        QByteArray ba;
        std::copy(packet.begin(), packet.end(), std::back_inserter(ba));
        mandala->downlinkReceived(ba);
        packet.clear();
        qApp->processEvents();
        ui->labelErrorsCount->setText(QString("Errors: %1").arg(errorsCount));
        ui->labelPacketsCount->setText(QString("Packets: %1").arg(packetsCount));
    }
    var->rec->setRecording(false);
    var->rec->close();
}
