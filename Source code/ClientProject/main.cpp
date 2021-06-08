#include <winsock2.h>
#include <iostream>

#include "paper2.h"
#include <QApplication>
#include <mainwindow.h>
#include "QtWindowCustomStyle\DarkStyle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Paper2* w=new Paper2;
    FramelessWindow framelessWindow;
    //framelessWindow.setContent(w);


    /*framelessWindow.resize(345,520);
    framelessWindow.setWindowIcon(QIcon("WindowIcon.png"));
    framelessWindow.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);*/

    MainWindow* M=new MainWindow();
    FramelessWindow framelessWindow2;
    framelessWindow2.setContent(M);

    framelessWindow2.resize(660,500);
    //framelessWindow2.setWindowIcon(QIcon("WindowIcon.png"));
    framelessWindow2.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    //framelessWindow.show();
    framelessWindow2.show();
    a.setStyle(new DarkStyle);
    //w->show();
    M->show();


    a.exec();
    return 0;
}
