#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}



QByteArray MainWindow::getFormData() const
{
    packageTpv a;
    qDebug() << sizeof(a);
    QByteArray data(reinterpret_cast<const char*>(&a), sizeof(packageTpv));
    qDebug() << data.size();
    return data;
}

MainWindow::~MainWindow()
{
    delete ui;
}

