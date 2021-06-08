#pragma once
#ifndef PAPER2_H
#define PAPER2_H
#define DEFAULT_PORT "27015"
#define DEFAULT_BUFFLEN 512

#include <iostream>
#include <thread>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <QWidget>
#include <qlabel.h>
#include <Qdir>
#include "QtWindowCustomStyle\framelesswindow\framelesswindow.h"
#include<QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Paper2;}
QT_END_NAMESPACE

class fara: public QMainWindow{
public:
    fara();
};


class Paper2;


class MyLabel: public QLabel
{
private:
    Paper2* papa;   // клас реімплементованого вікна, на якому буде розміщений цей об'єкт - *this
    short casel;    //номер ініціалізування
public:
    MyLabel(Paper2 *parent, short casel, const QString& text="");//констр. для ініціалізації номером лейбла
    void mouseReleaseEvent(QMouseEvent *ev);        // слот для опрацювання вибору юзера


};






class Paper2 : public QWidget
{
    //Q_OBJECT //макрос для декларування деяких сигналів, слотів які використовують сервіс служби QT MOS (meta object system)

public:
    Paper2(QWidget* p = nullptr);
    ~Paper2();

    Ui::Paper2 *ui;     //вказівник на клас форми, в якому розміщений код параметрів об'єктів (об'єкти, розміри, координати)
    //static int shared;
    QLabel lbl1;
    int shared;//its my choice for server sending
    int myChoice;//my choice for determination saved for later calculations
    int opChoice;//opponent choice
    int myscore;
    void opSet(int=0);

private:
};

void conn(Paper2*);
void receive_message(SOCKET*,Paper2*);
void determine(Paper2*);
void winner(Paper2* wid);
extern QString path;




#endif // PAPER2_H
