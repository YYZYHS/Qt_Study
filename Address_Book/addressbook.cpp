#include "addressbook.h"


addressbook::addressbook(QWidget *parent)
    : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;
    nameLine->setReadOnly(true);                            //设置为只读

    QLabel *addressLabel = new QLabel(tr("Address:"));
    addressText = new QTextEdit;
    addressText->setReadOnly(true);                         //设置为只读

    addButton = new QPushButton(tr("&Add"));
    addButton->show();
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();
    canceButton = new QPushButton(tr("&Cancel"));
    canceButton->hide();

    /*实例化浏览用按钮，但只有地址簿中有多个联系人时才会其用浏览功能*/
    nextButton = new QPushButton(tr("&Next"));
    nextButton->setEnabled(false);
    previousButton = new QPushButton(tr("&Previous"));
    previousButton->setEnabled(false);

    /*编辑与删除按钮*/
    editButton = new QPushButton(tr("&Edit"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
    removeButton->setEnabled(false);

    /*查找功能*/
    findButton = new QPushButton(tr("&Find"));
    findButton->setEnabled(false);
    dialog = new FindDialog;

    /*附加功能*/
    exportButton = new QPushButton(tr("E&xport"));
    exportButton->setToolTip(tr("Export as vCard"));
    exportButton->setEnabled(false);

    /*保存和加载功能*/
    loadButton = new QPushButton(tr("&Load..."));
    loadButton->setToolTip(tr("Load contacts from a file"));
    saveButton = new QPushButton(tr("Sa&ve..."));
    saveButton->setToolTip(tr("Save contacts to a file"));
    saveButton->setEnabled(false);

    /*信号与槽*/
    connect(addButton,SIGNAL(clicked()),this,SLOT(addContact()));
    connect(submitButton,SIGNAL(clicked()),this,SLOT(submitContact()));
    connect(canceButton,SIGNAL(clicked()),this,SLOT(cancelContact()));
    connect(nextButton,SIGNAL(clicked()),this,SLOT(next()));
    connect(previousButton,SIGNAL(clicked()),this,SLOT(previous()));
    connect(editButton, SIGNAL(clicked()), this, SLOT(editContact()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeContact()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findContact()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFromFile()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveToFile()));
    connect(exportButton, SIGNAL(clicked()), this, SLOT(exportAsVCard()));

    /*按钮组1布局：垂直布局*/
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(addButton,Qt::AlignTop);
    buttonLayout->addWidget(submitButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(canceButton);
    buttonLayout->addStretch();                             //确保按钮并不是采用均匀间隔排列的，而是更靠近widget 的顶部
    buttonLayout->addWidget(findButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(exportButton);

    /*按钮组2布局：水平布局*/
    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);

    QGridLayout *mainLayout = new QGridLayout;              //网格布局
    mainLayout->addWidget(nameLabel,0,0);
    mainLayout->addWidget(nameLine,0,1);
    mainLayout->addWidget(addressLabel,1,0,Qt::AlignTop);   //AlignTop确保其不会纵向放置在单元格 (1,0) 中央
    mainLayout->addWidget(addressText,1,1);
    mainLayout->addLayout(buttonLayout,1,2);
    mainLayout->addLayout(buttonLayout2,3,1);

    setLayout(mainLayout);
    setWindowTitle("Simple Address Book");
}

addressbook::~addressbook()
{
}

void addressbook::addContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();

    /*清空*/
    nameLine->clear();
    addressText->clear();
    updateInterface(AddingMode);

//    /*关闭只读，设置输入焦点*/
//    nameLine->setReadOnly(false);
//    nameLine->setFocus(Qt::OtherFocusReason);
//    addressText->setReadOnly(false);

//    /*显示提交和取消按钮*/
//    addButton->setEnabled(false);
//    submitButton->show();
//    canceButton->show();

//    /*禁用浏览相关的按钮*/
//    nextButton->setEnabled(false);
//    previousButton->setEnabled(false);
}

void addressbook::submitContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    /*确保保存字段不为空*/
    if(name.isEmpty()|| address.isEmpty())
    {
        QMessageBox::information(this,tr("Empty Field!"),
                                 tr("Please enter a name and address."));
        return;
    }

    /*检查是否在AddingMode模式下*/
    if(currentMode == AddingMode)
    {

        /*检查联系人是否已存在*/
        if(!contacts.contains(name))
        {
            contacts.insert(name,address);                      //保存字段
            QMessageBox::information(this,tr("Add Successful!"),
                                     tr("\"%1\" has been add to your address book.").arg(name));
        }
        else
        {
            QMessageBox::information(this,tr("Add Unsuccessful"),
                                     tr("Sorry,\"%1\" is already in your address book.").arg(name));
        }
    }
    /*检查是否在EditingMode模式下*/
    else if(currentMode == EditingMode)
    {
        if (oldName != name)
        {
            if (!contacts.contains(name))
            {
                QMessageBox::information(this, tr("Edit Successful"),
                                         tr("\"%1\" has been edited in your address book.").arg(oldName));
                contacts.remove(oldName);
                contacts.insert(name, address);
            }
            else
            {
                QMessageBox::information(this, tr("Edit Unsuccessful"),
                                         tr("Sorry, \"%1\" is already in your address book.").arg(name));
            }
        }
        else if(oldAddress != address)
        {
            QMessageBox::information(this,tr("Edit Successful"),
                                     tr("\"%1\" has been edited in your address book.").arg(name));
            contacts[name] = address;
        }

    }
    updateInterface(NavigationMode);
//    /*将按钮恢复正常*/
//    if(contacts.isEmpty())
//    {
//        nameLine->clear();
//        address.clear();
//    }

//    nameLine->setReadOnly(true);
//    addressText->setReadOnly(true);
//    addButton->setEnabled(true);
//    submitButton->hide();
//    canceButton->hide();

//    /*视情况决定是否恢复浏览按钮*/
//    int count = contacts.size();
//    nextButton->setEnabled(count > 1);
//    previousButton->setEnabled(count > 1);

}

void addressbook::cancelContact()
{
    //回复上次显示的联系人详细信息
    nameLine->setText(oldName);
    //nameLine->setReadOnly(true);

    addressText->setText(oldAddress);
    //addressText->setReadOnly(true);
    updateInterface(NavigationMode);
//    //其用addbutton,同时隐藏另外两个按钮
//    addButton->setEnabled(true);
//    submitButton->hide();
//    canceButton->hide();

//    /*视情况决定是否恢复浏览按钮*/
//    int count = contacts.size();
//    nextButton->setEnabled(count > 1);
//    previousButton->setEnabled(count > 1);

}

void addressbook::next()
{
    QString name = nameLine->text();
    QMap<QString,QString>::iterator i = contacts.find(name);

    if(i != contacts.end())
        i++;
    if(i == contacts.end())
        i = contacts.begin();
    nameLine->setText(i.key());
    addressText->setText(i.value());
}

void addressbook::previous()
{
    QString name = nameLine->text();
    QMap<QString,QString>::iterator i = contacts.find(name);
    if(i == contacts.end())
    {
        nameLine->clear();
        addressText->clear();
        return;
    }

    if (i == contacts.begin())
        i = contacts.end();             //end是等待输入的，不可显示

    i--;

    nameLine->setText(i.key());
    addressText->setText(i.value());
}

void addressbook::editContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();
    updateInterface(EditingMode);
}

void addressbook::removeContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if (contacts.contains(name))
    {
        int button = QMessageBox::question(this,
                                           tr("Confirm Remove"),
                                           tr("Are you sure you want to remove \"%1\"?").arg(name),
                                           QMessageBox::Yes | QMessageBox::No);
        if (button == QMessageBox::Yes)
        {
            previous();
            contacts.remove(name);

            QMessageBox::information(this, tr("Remove Successful"),
                                     tr("\"%1\" has been removed from your address book.").arg(name));
        }
    }
    updateInterface(NavigationMode);
}

void addressbook::updateInterface(Mode mode)
{
    currentMode = mode;

         switch (currentMode) {

         case AddingMode:
         case EditingMode:

             nameLine->setReadOnly(false);
             nameLine->setFocus(Qt::OtherFocusReason);
             addressText->setReadOnly(false);

             addButton->setEnabled(false);
             editButton->setEnabled(false);
             removeButton->setEnabled(false);

             nextButton->setEnabled(false);
             previousButton->setEnabled(false);

             submitButton->show();
             canceButton->show();

             loadButton->setEnabled(false);
             saveButton->setEnabled(false);
             exportButton->setEnabled(false);
             break;
         case NavigationMode:

             if (contacts.isEmpty()) {
                 nameLine->clear();
                 addressText->clear();
             }

             nameLine->setReadOnly(true);
             addressText->setReadOnly(true);
             addButton->setEnabled(true);

             int number = contacts.size();
             editButton->setEnabled(number >= 1);
             removeButton->setEnabled(number >= 1);
             findButton->setEnabled(number > 2);
             nextButton->setEnabled(number > 1);
             previousButton->setEnabled(number >1 );

             submitButton->hide();
             canceButton->hide();

             exportButton->setEnabled(number >= 1);

             loadButton->setEnabled(true);
             saveButton->setEnabled(number >= 1);
             break;
         }
}

void addressbook::findContact()
{
    dialog->show();

    if (dialog->exec() == QDialog::Accepted)
    {
        QString contactName = dialog->getFindText();

        if (contacts.contains(contactName))
        {
            nameLine->setText(contactName);
            addressText->setText(contacts.value(contactName));
        }
        else
        {
            QMessageBox::information(this, tr("Contact Not Found"),
                                     tr("Sorry, \"%1\" is not in your address book.").arg(contactName));
            return;
        }
    }
    updateInterface(NavigationMode);
}

void addressbook::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Address Book"), "",
                                                    tr("Address Book (*.abk);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << contacts;
    }
}

void addressbook::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Address Book"), "",
                                                    tr("Address Book (*.abk);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
        return;
        }
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        contacts.empty();
        in >> contacts;
        if (contacts.isEmpty())
        {
            QMessageBox::information(this, tr("No contacts in file"),
                                     tr("The file you are attempting to open contains no contacts."));
        }
        else
        {
            QMap<QString, QString>::iterator i = contacts.begin();
            nameLine->setText(i.key());
            addressText->setText(i.value());
        }
    }
    updateInterface(NavigationMode);
}

void addressbook::exportAsVCard()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();
    QString firstName;
    QString lastName;
    QStringList nameList;

    int index = name.indexOf(" ");

    if (index != -1)
    {
        nameList = name.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        firstName = nameList.first();
        lastName = nameList.last();
    }
    else
    {
        firstName = name;
        lastName = "";
    }

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Export Contact"), "",
                                                    tr("vCard Files (*.vcf);;All Files (*)"));

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"),
                                 file.errorString());
        return;
    }
    QTextStream out(&file);
    out << "BEGIN:VCARD" << "\n";
    out << "VERSION:2.1" << "\n";
    out << "N:" << lastName << ";" << firstName << "\n";

    if (!nameList.isEmpty())
        out << "FN:" << nameList.join(" ") << "\n";
    else
        out << "FN:" << firstName << "\n";

    address.replace(";", "\\;", Qt::CaseInsensitive);
    address.replace("\n", ";", Qt::CaseInsensitive);
    address.replace(",", " ", Qt::CaseInsensitive);

    out << "ADR;HOME:;" << address << "\n";
    out << "END:VCARD" << "\n";

    QMessageBox::information(this, tr("Export Successful"),
    tr("\"%1\" has been exported as a vCard.").arg(name));
}
