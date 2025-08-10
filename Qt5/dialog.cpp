#include "dialog.h"
#include "ui_dialog.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dialog::updateDataFromRust);
    timer->start(1000);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::updateDataFromRust()
{
    const char* json_str = get_system_metrics_json();
    if (json_str) {
        QString json_qstr = QString::fromUtf8(json_str);
        free_string((char*)json_str);

        QJsonDocument doc = QJsonDocument::fromJson(json_qstr.toUtf8());
        QJsonObject obj = doc.object();

        ui->barCPU1->setValue(obj["cpu_usage"].toDouble());
        ui->freqCPU1->setText(QString::number(obj["cpu_freq"].toDouble() / 1000000.0, 'f', 2) + " GHz");

        ui->barGPU->setValue(obj["gpu_usage"].toDouble());
        ui->freqGPU->setText(QString::number(obj["gpu_freq"].toDouble() / 1000000.0, 'f', 2) + " GHz");

        ui->barNPU1->setValue(obj["npu_usage"].toDouble());
        ui->freqNPU1->setText(QString::number(obj["npu_freq"].toDouble() / 1000000.0, 'f', 2) + " GHz");

        ui->barRGA1->setValue(obj["rga_usage"].toDouble());
        ui->freqRGA1->setText(QString::number(obj["rga_aclk_freq"].toDouble() / 1000000.0, 'f', 2) + " GHz");

        ui->barMem->setValue(obj["memory_usage"].toDouble());
        ui->barSwap->setValue(obj["swap_usage"].toDouble());

        ui->barTemp->setValue(obj["temperature"].toDouble() / 1000.0);
        ui->freqTemp->setText(QString::number(obj["temperature"].toDouble() / 1000.0, 'f', 1) + " °C");

        ui->barFan->setValue(obj["fan_state"].toInt());
    }
}