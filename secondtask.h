#ifndef SECONDTASK_H
#define SECONDTASK_H

#include <QDialog>
#include <QTextBrowser>

namespace Ui {
class SecondTask;
}

class SecondTask : public QDialog
{
    Q_OBJECT

public:
    explicit SecondTask(QWidget *parent = nullptr);
    ~SecondTask();
    std::vector<QString> forbiddenWorlds = { "Sunday", "Monday", "Tuesday","Wednesday", "Thirsday", "Friday", "Saturday" };
    QString outfw;

private slots:
    void on_pushButton_clicked();

private:
    Ui::SecondTask *ui;
};

class NewTextBrowser{
private:
    QTextBrowser *ptr;
    std::vector<QString> fw = { "Sunday", "Monday", "Tuesday","Wednesday", "Thirsday", "Friday", "Saturday" };
    bool answer = false;
public:
    NewTextBrowser(){ // Конструктор класса
        ptr = new QTextBrowser;
    };

    bool append(QString text){
        for(std::size_t i = 0; i < fw.size(); i++)
        {// Проверка на наличие запрещенных слов в сообщении
            if(text.contains(fw[i])&&!answer)
                answer = true;
        };

        if(!answer) // Если в тексте не содержится запрещенных слов, то добавляем этот текст
            ptr->append(text);

        return answer;
    };

    ~NewTextBrowser(){// Деструктор класса
        delete ptr;
    };
};

#endif // SECONDTASK_H
