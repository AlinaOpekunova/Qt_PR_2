#ifndef THIRDTASK_H
#define THIRDTASK_H

#include <QDialog>
#include <QComboBox>

namespace Ui {
class ThirdTask;
}

class ThirdTask : public QDialog
{
    Q_OBJECT

public:
    explicit ThirdTask(QWidget *parent = nullptr);
    ~ThirdTask();

private slots:


    void on_loadButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::ThirdTask *ui;
    QComboBox *comboBox;
};

#endif // THIRDTASK_H
