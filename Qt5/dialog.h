#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QProgressBar>
#include <QTimer>
#include <QProcess>
#include <QDebug>
#include <QString>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <unordered_map>

#include "rtop_rust.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void updateDataFromRust(void);

private:
    Ui::Dialog *ui;
    QTimer *timer;
};
#endif // DIALOG_H
