#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#pragma execution_character_set("utf-8")
int main(int argc, char *argv[])
{
    //C:\Qt\Qt5.10.1\5.10.1\msvc2013_64\include\QtCore\qstringview.h:178: error: C1001: 编译器中发生内部错误。
    // https://forum.qt.io/topic/88001/helloworld-5-10-1-msvc2013-build-fails-in-qstringview-h
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
#else
QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
