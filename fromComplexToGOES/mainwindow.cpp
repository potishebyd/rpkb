#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    form = new SecondForm;
   connect(form, &SecondForm::ToMainWindow, this, &MainWindow::show);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{

}


void MainWindow::on_action_2_triggered()
{


    this->hide();
    form->show();
}


void MainWindow::on_action_3_triggered()
{
    QApplication::quit();
}


void MainWindow::on_action_4_triggered()
{
    this->hide();
    form->show();
}

