#pragma once

#include <QMainWindow>

#include "ui_mainwindow.h"
#include <fstream>
#include <istream>
#include <QFile>
#include <QPushButton>
#include <QDir>
#include <QString>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "paper2.h"
#include "SideChat.h"
#include "profilen.h"


namespace Ui {
class MainWindow;
}
class MainWindow;
class menuLabel: public QLabel
{
    Q_OBJECT
public:
    menuLabel();
    void construct(QWidget* parent, QLabel* rep,MainWindow* mw,QString id);
    QString id;
    MainWindow* mw;
signals:
    void myLabelClicked();
protected:
    bool event(QEvent *myEvent);

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:



public:
    explicit MainWindow(QWidget *parent = nullptr);
    void createGame(QString pl1, QString rating);
    void fillInfo(int num,QString score,QString player_name);
    void scoreEditor(QString,QString);
    ~MainWindow();
    bool auth;
    unsigned int gameCount;
    QString gameid;
    Ui::MainWindow *ui;
    QString player_name;
    menuLabel add;
    menuLabel mm;
    menuLabel menu;
    menuLabel profile;
    menuLabel settings;
    menuLabel coins;
    QString player_rating;
    Paper2* gm;
    SideChat* sd;
    Profilen* prf;


private slots:
    void on_bReg_clicked();
    void on_bLogin_clicked();
    void on_pl2_linkActivated(const QString &link);
    void on_join_clicked();
    void on_join_2_clicked();
    void on_join_3_clicked();
    void on_join_4_clicked();
    void on_join_5_clicked();
    void on_signal_add_clicked();
    void on_pb_clicked();

    void on_pushButton_clicked();
    void on_closeChat_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

void refresher(MainWindow*);
void receiver(MainWindow*);
void frameFormer(MainWindow*);
void scoreChanged(MainWindow*);
void chatting(MainWindow*);
void moving_effect(MainWindow*, int casel);
/*class Label: public QLabel
{
public:
    Label(QWidget *parent,QLabel* par);//констр. для ініціалізації номером лейбла
    void mouseReleaseEvent(QMouseEvent *ev);        // слот для опрацювання вибору юзера
};*/



