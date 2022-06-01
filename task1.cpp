#include "task1.h"
#include "ui_task1.h"
#include "dialog.h"

Task1::Task1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Task1)
{
    ui->setupUi(this);
}

Task1::~Task1()
{
    delete ui;
}

void Task1::on_pushButton_clicked()
{
    ErrorMessage *n = new ErrorMessage;
    n->setStyleDialog();
    n->show();
}


void Task1::on_pushButton_2_clicked()
{
    InputTextMessage *i = new InputTextMessage;
    i->setStyleDialog();
    i->show();
}


void Task1::on_pushButton_3_clicked()
{
    ConfirmMesssage *c = new ConfirmMesssage;
    c->setStyleDialog();
    c->show();
}


void Task1::on_pushButton_4_clicked()
{
    ChooseMessage *h = new ChooseMessage;
    h->setStyleDialog();
    h->show();
}

