#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>

#include <QMandala.h>
#include "EscReader.h"

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

    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    EscReader reader;
    QMandalaItem m(nullptr, true);
    connect(&reader, &EscReader::packet_read, &m, &QMandalaItem::downlinkReceived);

    m.rec->setRecording(true);
    m.rec->uavNameOverride = ui->lineEditTelemetryName->text();

    auto tp1 = std::chrono::high_resolution_clock::now();
    size_t bytesReaded = 0;
    while(!file.atEnd())
    {
        QByteArray data = file.read(512);
        bytesReaded += data.size();
        reader.push(data);

        auto tp2 = std::chrono::high_resolution_clock::now();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count() > 100)
        {
            tp1 = tp2;
            qApp->processEvents();
        }
        ui->labelBytes->setText(QString("Bytes processed: %1/%2").arg(bytesReaded).arg(file.size()));
    }
    m.rec->setRecording(false);
    m.rec->close();
    ui->labelBytes->setText("FINISHED");
}
