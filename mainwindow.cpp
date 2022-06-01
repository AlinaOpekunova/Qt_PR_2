#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task1.h"
#include "secondtask.h"
#include "thirdtask.h"

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


void MainWindow::on_pushButton_task1_clicked()
{
    Task1 window;
    window.setModal(true);
    window.exec();
}


void MainWindow::on_pushButton_task2_clicked()
{
    SecondTask window;
    window.setModal(true);
    window.exec();
}


void MainWindow::on_pushButton_task3_clicked()
{
    ThirdTask window;
    window.setModal(true);
    window.exec();
}

