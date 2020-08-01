#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow w;
    w.show();

    return a.exec();
}



/*
struct DATA
{
    char type;
    char name[14];
    char data[1013];
}
*/
/*
例子：
P#614400#.......   :这是一张新的图片，大小为614000
T...........:这是环境数据
*/

