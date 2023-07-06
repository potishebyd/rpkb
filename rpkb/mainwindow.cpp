#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

data_t MainWindow::collectFormData() const
{
    data_t a;
    a.id = 20;
    qstrncpy(a.model, "str", 10);
    return a;
}

QByteArray MainWindow::getFormData() const
{
    data_t a = collectFormData();
    QByteArray data(reinterpret_cast<const char*>(&a), sizeof(data_t));
    return data;
}

MainWindow::~MainWindow()
{
    delete ui;
}

