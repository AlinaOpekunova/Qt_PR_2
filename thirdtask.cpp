#include "thirdtask.h"
#include "ui_thirdtask.h"

#include<QVector>
#include <iostream>
#include <QTime>
#include <QMap>
#include <QList>

using namespace std;

ThirdTask::ThirdTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThirdTask)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(5);
    ui->comboBox->addItem("Выбрать..");
}

ThirdTask::~ThirdTask()
{
    delete ui;
}

class Memento
{
    QVector<QString> *vector;
    QString *time;
public:
    Memento(QVector<QString> *vector_, QString *time_)
    {
        this->vector = vector_;
        this->time = time_;
    }
};

class History{
    QMap<QString, QVector<QString>> *history;
public:
    History(){
        history = new QMap<QString, QVector<QString>>;
    };
    void addNew(QVector<QString> *vec, QString time){
        history->insert(time, *vec);
    };

    QVector<QString> getVector(QString time){
        return history->value(time);
    }
};

QVector<QString>* saveTable(QTableWidget* table)
{
    QVector<QString>  *vectorItems = new QVector<QString>;
    const int nColumn = table->columnCount();
    const int nRow = table->rowCount();

    for(int i = 0; i < nRow; i++){
        for(int j = 0; j < nColumn; j++){
            if(table->item(i,j)== NULL){vectorItems->push_back("");}
            else{vectorItems->push_back(table->item(i,j)->text());}
        };
    };
    return vectorItems;
};

void loadTable(QVector<QString> vectorItems, QTableWidget* resTable)
{
    const int nColumn = resTable->columnCount();
    const int nRow = resTable->rowCount();

    for(int i = 0; i < nRow; i++){
        for(int j = 0; j < nColumn; j++){
            QTableWidgetItem* item = new QTableWidgetItem(vectorItems[i*nColumn+j]);
            resTable->setItem(i, j, item);
        };
    }
};

History *hist = new History;


void ThirdTask::on_loadButton_clicked()
{
    loadTable(hist->getVector(ui->comboBox->currentText()),ui->tableWidget);
}

void ThirdTask::on_saveButton_clicked()
{
    ui->comboBox->addItem(QTime::currentTime().toString());
    hist->addNew(saveTable(ui->tableWidget),QTime::currentTime().toString());
}
