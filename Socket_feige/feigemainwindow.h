#ifndef FEIGEMAINWINDOW_H
#define FEIGEMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QFile>


class FeigeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    FeigeMainWindow(QWidget *parent = nullptr);
    ~FeigeMainWindow();
};
#endif // FEIGEMAINWINDOW_H
