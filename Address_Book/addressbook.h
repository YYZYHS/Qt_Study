#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>
#include <QPushButton>
#include <QMap>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "finddialog.h"
//#include <QFile>
#include <QFileDialog>
#include <QDataStream>
#include <QTextStream>

class addressbook : public QWidget
{
    Q_OBJECT

public:
    addressbook(QWidget *parent = nullptr);
    enum Mode { NavigationMode, AddingMode, EditingMode };
    ~addressbook();


public slots:
    /*Step2：声明槽*/
    void addContact();          //添加槽
    void submitContact();       //提交槽
    void cancelContact();       //取消槽
    void next();
    void previous();
    void editContact();
    void removeContact();
    void findContact();
    void saveToFile();
    void loadFromFile();
    void exportAsVCard();
private:
    /*Step1：声明输入框*/
    //这是两个全局变量
    QLineEdit *nameLine;        //声明用户名输入框
    QTextEdit *addressText;     //声明地址输入框

    /*Step2：声明按钮*/
    QPushButton *addButton;     //添加按钮
    QPushButton *submitButton;  //提交按钮
    QPushButton *canceButton;   //取消按钮

    QMap<QString,QString> contacts;
    //contacts带有一个键-值对：联系人姓名作为键,而联系人地址作为值
    QString oldName;            //点击添加时最后显示的联系人姓名
    QString oldAddress;         //点击添加时最后显示的地址

    /*Step3:浏览地址簿条目*/
    QPushButton *nextButton;
    QPushButton *previousButton;

    /*Step4：模式转换以及编辑删除*/
    QPushButton *editButton;    //编辑按钮
    QPushButton *removeButton;  //删除按钮
    Mode currentMode;           //追踪当前模式
    void updateInterface(Mode mode);//模式更新

    /*Step5:查找功能*/
    QPushButton *findButton;
    FindDialog *dialog;

    /*Step6:保存和读取*/
    QPushButton *loadButton;
    QPushButton *saveButton;

    /*附加功能*/
    QPushButton *exportButton;

};
#endif // ADDRESSBOOK_H
