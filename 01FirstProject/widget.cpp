﻿#include "widget.h"


// 命名规范
// 类名 首字母大写，单词和单词之间首字母大写
// 函数名 变量名称 首字母小写，单词和单词之间首字母大写

//快捷键
//注释  ctrl + /
//运行  ctrl + r
//编译  ctrl + b
//字体缩放 ctrl + 鼠标滚轮
//查找  ctrl + f
//整行移动 ctrl + shift + ↑ 或者↓
//帮助文档 F1
//自动对齐  ctrl + i;
//同名之间的.h 和 .cpp切换  F4

//帮助文档 第一种方式 F1  第二种 左侧按钮  第三种 C:\Qt\Qt5.6.0\5.6\mingw49_32\bin

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

