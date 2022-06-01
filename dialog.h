#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "QGridLayout"
#include "QTextEdit"
#include "QPushButton"
#include "QLabel"
#include "QLineEdit"
#include "QToolBar"
#include "QComboBox"
#include <QFileSystemModel>
#include <QTreeView>
#include <QSplitter>


namespace Ui {
class Dialog;
}

namespace ErM {class ErrorMessage;}

namespace InM {class InputTextMessage;}

namespace CoM {class ConfirmMesssage;}

namespace ChM {class ChooseMessage;}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    virtual void setStyleDialog()=0;
    ~Dialog();


private:
    Ui::Dialog *ui;
};

class ErrorMessage : public Dialog
{
    Q_OBJECT

public:
    explicit ErrorMessage(QWidget *parent = nullptr){};
    void setStyleDialog(){
        QGridLayout * grid = new QGridLayout(this);
        setWindowTitle("Окно с сообщением об ошибке");
        setGeometry(100,100,150,120);
        QLabel * plb = new QLabel(tr(error), this);
        grid->addWidget(plb, 0,0);
        plb->setStyleSheet(QString("color: red; font-size: %1px").arg(14));

        cancel = new QPushButton(tr("Закрыть"), this);
        cancel->setStyleSheet(QString("font-size: %1px").arg(14));
        grid->addWidget(cancel, 1,0);
        // при нажатии на кнопку окно закроется:
        connect(cancel,&QPushButton::clicked,this,&QDialog::reject);
    };
    ~ErrorMessage(){
        delete error;
        delete cancel;
        delete erm;
    };

private:
    ErM::ErrorMessage *erm;
    const char *error = "Ошибка!"; // название ошибки
    QPushButton *cancel; // кнопка
};

class InputTextMessage : public Dialog
{
    Q_OBJECT

public:
    explicit InputTextMessage(QWidget *parent = nullptr){};
    void setStyleDialog(){
        QGridLayout * grid = new QGridLayout(this);
        setWindowTitle("Окно ввода текста");
        setGeometry(100,100,500,250);

        toolBar = new QToolBar(tr("File"), this);
        QAction *openAction = new QAction(tr("&Кнопка 1"), this);
        QAction *saveAction = new QAction(tr("&Кнопка 2"), this);
        QAction *exitAction = new QAction(tr("&Кнопка 3"), this);

        toolBar->addAction(openAction);
        toolBar->addSeparator();
        toolBar->addAction(saveAction);
        toolBar->addSeparator();
        toolBar->addAction(exitAction);

        grid->addWidget(toolBar, 0,0);
        toolBar->setStyleSheet(QString("background-color: white; color: blue; font-size: %1px").arg(12));

        textBox = new QTextEdit(tr("Введите текст.."), this);
        textBox->setStyleSheet(QString("font-size: %1px").arg(14));
        grid->addWidget(textBox, 1,0);

        undoButton = new QPushButton(tr("Отменить"), this);
        undoButton->setStyleSheet(QString("background-color: blue; color: white; font-size: %1px").arg(14));
        grid->addWidget(undoButton, 0,1);


        confirm = new QPushButton(tr("Подтвердить"), this);
        confirm->setStyleSheet(QString("background-color: blue; color: white; font-size: %1px").arg(14));
        grid->addWidget(confirm, 1,1);

        connect(undoButton,&QPushButton::clicked,textBox,&QTextEdit::clear);
        connect(confirm,&QPushButton::clicked,this,&QDialog::reject);
    };
    ~InputTextMessage(){
        delete confirm;
        delete undoButton;
        delete toolBar;
        delete textBox;
        delete inm;
    };

private:
    InM::InputTextMessage *inm;
    QToolBar *toolBar;
    QPushButton *confirm;
    QPushButton *undoButton;
    QTextEdit *textBox;
};

class ConfirmMesssage : public Dialog
{
    Q_OBJECT

public:
    explicit ConfirmMesssage(QWidget *parent = nullptr){};
    void setStyleDialog(){
        QGridLayout * grid = new QGridLayout(this);
        setWindowTitle("Окно подтверждения");
        setGeometry(100,100,150,120);

        QLabel * message = new QLabel(tr(label), this);
        message->setStyleSheet(QString("font-weight: bold; color: green; font-size: %1px").arg(14));
        grid->addWidget(message, 0,0);

        cancelButton = new QPushButton(tr("Отменить"), this);
        cancelButton->setStyleSheet(QString("background-color: white; color: gray; font-size: %1px").arg(14));
        grid->addWidget(cancelButton, 1,0);

        confirmButton = new QPushButton(tr("Подтвердить"), this);
        confirmButton->setStyleSheet(QString("background-color: white; color: gray; font-size: %1px").arg(14));
        grid->addWidget(confirmButton, 1,1);

        connect(cancelButton,&QPushButton::clicked,this,&QDialog::reject);
        connect(confirmButton,&QPushButton::clicked,this,&QDialog::reject);
    };
    ~ConfirmMesssage(){
        delete confirmButton;
        delete cancelButton;
        delete label;
        delete com;
    };

private:
    CoM::ConfirmMesssage *com;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
    const char *label = "Вы подтверждаете действия?";
};

class ChooseMessage : public Dialog
{
    Q_OBJECT

public:
    explicit ChooseMessage(QWidget *parent = nullptr){};
    void setStyleDialog(){
        QGridLayout * grid = new QGridLayout(this);
        setWindowTitle("Окно выбора файла");
        setGeometry(100,100,500,500);

        QSplitter *splitter = new QSplitter;
        model = new QFileSystemModel;
        model->setRootPath(QDir::currentPath());
        QTreeView *tree = new QTreeView(splitter);
        tree->setModel(model);
        tree->setRootIndex(model->index(QDir::currentPath()));
        grid->addWidget(tree, 1,0,3,4);

        filename = new QLineEdit(this);
        grid->addWidget(filename, 0,0);
        filename->setStyleSheet(QString("font-size: %1px").arg(14));

        comboBox = new QComboBox(this);
        grid->addWidget(comboBox, 0,1);
        comboBox->addItems({".txt",".doc",".docx",".pdf",".fb2"});
        comboBox->setStyleSheet(QString("background-color: blue; color: white; font-size: %1px").arg(14));

        openButtom = new QPushButton(tr("Открыть"), this);
        openButtom->setStyleSheet(QString("background-color: blue; color: white; font-size: %1px").arg(14));
        grid->addWidget(openButtom, 0,2);

        canButtom = new QPushButton(tr("Отмена"), this);
        canButtom->setStyleSheet(QString("background-color: blue; color: white; font-size: %1px").arg(14));
        grid->addWidget(canButtom, 0,3);

        connect(comboBox,&QComboBox::currentTextChanged,this,&ChooseMessage::seType);
        connect(openButtom,&QPushButton::clicked,this,&QDialog::reject);
        connect(canButtom,&QPushButton::clicked,filename,&QLineEdit::clear);
    };
    ~ChooseMessage(){
        delete canButtom;
        delete openButtom;
        delete filename;
        delete comboBox;
        delete model;
        delete chm;
    };

public slots:
    void seType(){
        filename->setText(filename->text()+comboBox->currentText());
    };

private:
    ChM::ChooseMessage *chm;
    QLineEdit *filename;
    QComboBox *comboBox;
    QPushButton *openButtom;
    QPushButton *canButtom;
    QFileSystemModel *model;
};


#endif // DIALOG_H
