#include "secondtask.h"
#include "ui_secondtask.h"

#include <QString>
#include <QTextBrowser>
#include <QMessageBox>

SecondTask::SecondTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondTask)
{
    ui->setupUi(this);
    for(std::size_t i = 0; i < forbiddenWorlds.size(); i++){
        outfw.append(forbiddenWorlds[i]+'\n');
    }
    ui->outWords->setText(outfw);
}

SecondTask::~SecondTask()
{
    delete ui;
}

void SecondTask::on_pushButton_clicked()
{
    NewTextBrowser p; // Создаем экземпляр нового класса
    QString res = "";// Строка для вывода в QMessageBox
    if(!p.append(ui->inText->toPlainText())){
        // метод append возвращает false, если в сообщении нет запрещенных слов
        res = "Сообщение отправлено";
        ui->outResult->insertPlainText(ui->inText->toPlainText());
    }
    else {
        res = "Сообщение не отправлено\nИспользовано запрещенное слово!";}

    QMessageBox::information(this, "Результат",res);
}

