﻿#include "widget.h"

#include <QApplication>// 包含一个应用程序类的头文件

//main程序入口  argc命令行变量的数量  argv命令行变量的数组
int main(int argc, char *argv[])
{
    //a应用程序对象，在Qt中，应用程序对象有且仅有一个
    QApplication a(argc, argv);
    //窗口对象 mywidget父类 -> QWidget
    Widget w;
    //窗口对象默认是不会显示的，必须调用show方法显示窗口。
    w.show();

    //让应用程序对象进入消息循环
    //让代码阻塞在这行
    return a.exec();

    //return a.exec()的机制有点类似于下面

    //    while(true)
    //    {
    //         if(点击叉子)
    //        {
    //            break;
    //        }
    //    }

}
