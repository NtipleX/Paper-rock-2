

#include "mainwindow.h"
#include <windows.h>
SOCKET toServer=INVALID_SOCKET;
QString message ="-\0";
void Send()
{
    send(toServer,message.toLocal8Bit(),20,0);
}
void Send(QString msg)
{
    send(toServer,msg.toStdString().c_str(),20,0);

}
void endm()
{
    message="-\0";
}
void mstart(QString s)
{
    message=s;
    Sleep(100);
    Send(s+'\0');
}
void clearlog()
{
    send(toServer,"          loading\0",20,0);
    send(toServer,"         loading\0",20,0);
    send(toServer,"        loading\0",20,0);
    send(toServer,"       loading\0",20,0);
}
void debuglog(QLabel* db,QString mm)
{
    db->setText(db->text()+"\n"+mm);
}
void clearbuf(char* b,int n)
{
    for(int i=0;i<n;i++)
    {
        b[i]='\0';
    }
}
void start_effect(MainWindow* mm);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),gameid("--"),
    ui(new Ui::MainWindow)//, add(this,this->ui->add)

{

    gameCount=0;
    auth=false;
    ui->setupUi(this);
    //////////////////
    ui->groupBox->hide();
    ui->groupBox_2->hide();
    ui->groupBox_3->hide();
    ui->groupBox_4->hide();
    ui->groupBox_5->hide();


    ui->label_2->hide();
    ui->menu->hide();
    ui->profile->hide();
    ui->settings->hide();
    ui->mm->hide();
    ui->add->hide();
    ui->coins->hide();
    ui->coinst->hide();
    ui->mmr->hide();
    ui->mmrt->hide();
    QPixmap px;
    px.load("Resources/online.png");
    px=px.scaled(ui->coins->size(),Qt::KeepAspectRatio);
    ui->online_ico->setPixmap(px);
    ui->online_ico->show();

    static std::thread refresher_t(refresher,this);
    static std::thread receiver_t(receiver,this);
    gm=new Paper2();

    //add.show();

    gm->show();
    gm->hide();

    sd=new SideChat();
    sd->hide();
    ui->closeChat->hide();
    static std::thread(chatting);

    px=px.scaled(sd->ui->background->size(),Qt::KeepAspectRatio);
    px.load("Resources/background.jpg");
    sd->ui->background->setPixmap(px);
    ui->verticalSlider->hide();
    ui->pb->hide();
    ui->db->hide();
    //LOG IN
    /*ui->db->show();
    ui->login->setText("jimmy");
    ui->password->setText("123");
    ui->bLogin->click();*/
/**/
}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bReg_clicked()
{
    QString name = this->ui->login->text();
    QString psw = this->ui->password->text();
    QFile file("profiles.txt");
    file.open(QIODevice::Append);

    /*
     * "login:password;0,0,0,0,0,0,0,0$"
     * Number is value
     *
    */
    file.write(name.toUtf8());
    file.write(new char(':'),1);
    file.write(psw.toUtf8());
    file.write(new char(';'),1);
    QByteArray data("0,0,0,0,0,0,0,0$");
    file.write(data);
    file.close();
    ui->login->clear();
    ui->password->clear();
}

void MainWindow::on_bLogin_clicked()
{
    //username is login line
    //password is password line
    //luser is word read from file before :
    //lpass is word read from file before ;

    std::ifstream file;
    file.open("profiles.txt",std::ios::in);
    char luser[20];
    char lpass[20];
    char buf[50];
    char minibuf[10];

    QString username(this->ui->login->text());
    QString password(this->ui->password->text());

    while(true)
    {
        //buf index description
        //0 - player rating
        file.getline(luser,20,':');
        file.getline(lpass,20,';');
        file.getline(buf,50,'$');
        if(username==luser && password==lpass)
        {
            this->auth=1;
            this->ui->bReg->hide();
                    this->ui->bLogin->hide();
                    this->ui->checkBox->hide();
                    this->ui->label->hide();
                    this->ui->bLogin->hide();
            this->ui->login->hide();
            this->ui->password->hide();
            //SHOW PROFILE HERE
            QPixmap px;
            px.load("Resources/Profile_line.png");
            player_name=this->ui->login->text();
            ui->label_2->setPixmap(px);
            ui->nickname->setText(player_name);

            ui->login_failed->hide();

            px.load("Resources/menu.png");
            px=px.scaled(ui->menu->size(),Qt::KeepAspectRatio);
            ui->menu->setPixmap(px);
            ui->menu->show();


            px.load("Resources/profile.png");
            px=px.scaled(ui->menu->size(),Qt::KeepAspectRatio);
            ui->profile->setPixmap(px);
            px.load("Resources/settings.jpg");
            px=px.scaled(ui->menu->size(),Qt::KeepAspectRatio);
            ui->settings->setPixmap(px);
            px.load("Resources/mm.png");
            px=px.scaled(ui->menu->size(),Qt::KeepAspectRatio);
            ui->mm->setPixmap(px);
            px.load("Resources/add.png");
            px=px.scaled(ui->menu->size(),Qt::KeepAspectRatio);
            ui->add->setPixmap(px);
            px.load("Resources/coins.png");
            px=px.scaled(ui->coins->size(),Qt::KeepAspectRatio);
            ui->coins->setPixmap(px);
            px.load("Resources/rating.png");
            px=px.scaled(ui->coins->size(),Qt::KeepAspectRatio);
            ui->mmr->setPixmap(px);

            ui->profile->show();
            ui->settings->show();
            ui->mm->show();
            ui->add->show();
            ui->coins->show();
            ui->coinst->show();
            ui->mmr->show();
            ui->mmrt->show();
            ui->online->show();
            ui->online_ico->show();
            ui->label_2->show();
            //LOADING
            //rating
            QString tRating="";
            for(int p=0;p<50;p++)
            {
                if(buf[p]!=',')
                {
                    tRating+=buf[p];
                }
                else p=50;
            }
            ui->mmrt->setText(tRating);
            player_rating=tRating;

            mm.construct(this,this->ui->mm,this,"mm");
            menu.construct(this,this->ui->menu,this,"menu");
            profile.construct(this,this->ui->profile,this,"profile");
            settings.construct(this,this->ui->settings,this,"settings");
            coins.construct(this,this->ui->coins,this,"coins");
            add.construct(this,this->ui->add,this,"add");
            new std::thread(chatting,this);

            QPixmap efp("Resources/effect1.png");
            efp=efp.scaled(ui->effect1->size());
            ui->effect1->setPixmap(efp);
            ui->effect1_2->setPixmap(efp);
            ui->effect1_3->setPixmap(efp);
            ui->effect1_4->setPixmap(efp);
            efp.load("Resources/effect2.png");
            ui->effect1_5->setPixmap(efp);
            ui->effect1_6->setPixmap(efp);
            ui->effect1_6->hide();
            ui->effect1_5->hide();
            ui->effect1_4->hide();
            ui->effect1_3->hide();
            ui->effect1_2->hide();
            ui->effect1->hide();

            prf=new Profilen(player_name);

            ///////////////////
            break;
        }
        else
        {


            if(file.eof())
            {
                this->ui->login_failed->setText("Log in failed");
                break;
            }
        }
    }


    /*if(username==luser and password==lpass){

    }*/
    file.close();

}

void MainWindow::createGame(QString pl1, QString rating)
{
    QGroupBox* game[5]
    {this->ui->groupBox,
    this->ui->groupBox_2,
    this->ui->groupBox_3,
    this->ui->groupBox_4,
    this->ui->groupBox_5};
    QLabel* component[5][6]
    {
        {
            this->ui->rating,
            this->ui->pl1,
            this->ui->score,
            this->ui->pl2,
            this->ui->details,
            this->ui->watch
        },

        {
            this->ui->rating_2,
            this->ui->pl1_2,
            this->ui->score_2,
            this->ui->pl2_2,
            this->ui->details_2,
            this->ui->watch_2
        },
        {
            this->ui->rating_3,
            this->ui->pl1_3,
            this->ui->score_3,
            this->ui->pl2_3,
            this->ui->details_3,
            this->ui->watch_3
        },
        {
            this->ui->rating_4,
            this->ui->pl1_4,
            this->ui->score_4,
            this->ui->pl2_4,
            this->ui->details_4,
            this->ui->watch_4
        },
        {
            this->ui->rating_5,
            this->ui->pl1_5,
            this->ui->score_5,
            this->ui->pl2_5,
            this->ui->details_5,
            this->ui->watch_5
        },
    };

    game[gameCount]->setVisible(1);
    component[gameCount][0]->setText(rating);
    component[gameCount][1]->setText(pl1);
    component[gameCount][2]->setText("");
    component[gameCount][3]->setText("");
    component[gameCount][4]->setText("");
    component[gameCount][5]->setText("");
    component[gameCount][6]->setText("");
    gameCount++;

}


void MainWindow::fillInfo(int num, QString score="0:0",QString versus="")
{
    QGroupBox* game[5]
    {this->ui->groupBox,
    this->ui->groupBox_2,
    this->ui->groupBox_3,
    this->ui->groupBox_4,
    this->ui->groupBox_5};
    QLabel* component[5][6]
    {
        {
            this->ui->rating,
            this->ui->pl1,
            this->ui->score,
            this->ui->pl2,
            this->ui->details,
            this->ui->watch
        },

        {
            this->ui->rating_2,
            this->ui->pl1_2,
            this->ui->score_2,
            this->ui->pl2_2,
            this->ui->details_2,
            this->ui->watch_2
        },
        {
            this->ui->rating_3,
            this->ui->pl1_3,
            this->ui->score_3,
            this->ui->pl2_3,
            this->ui->details_3,
            this->ui->watch_3
        },
        {
            this->ui->rating_4,
            this->ui->pl1_4,
            this->ui->score_4,
            this->ui->pl2_4,
            this->ui->details_4,
            this->ui->watch_4
        },
        {
            this->ui->rating_5,
            this->ui->pl1_5,
            this->ui->score_5,
            this->ui->pl2_5,
            this->ui->details_5,
            this->ui->watch_5
        },
    };

    game[num]->setVisible(1);
    component[num][2]->setText(score);
    if(versus!=""){
        component[num][3]->setText(versus);
        component[num][4]->setText("Деталі");
        component[num][5]->setText("Дивтись");
        component[num][4]->setVisible(1);
        component[num][5]->setVisible(1);
        switch(num)
        {
        case 0:
        {
            this->ui->join->hide();
            break;
        }
        case 1:
        {
            this->ui->join_2->hide();
            break;
        }
        case 2:
        {
            this->ui->join_3->hide();
            break;
        }
        case 3:
        {
            this->ui->join_4->hide();
            break;
        }
        case 4:
        {
            this->ui->join_5->hide();
            break;
        }
        }
    }



    //game[num]->

}

//function receiver
void refresher(MainWindow* w)
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);



    struct addrinfo* result = NULL,
            * ptr = NULL,
            hints;



    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;


    int iResult =getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
            //printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            return;
        }


    //toServer=socket(result->ai_family, result->ai_socktype,
    //            result->ai_protocol);

    for (ptr = result; ptr != NULL;ptr = ptr->ai_next) {

            // Create a SOCKET for connecting to server
            toServer = socket(ptr->ai_family, ptr->ai_socktype,
                ptr->ai_protocol);
            if (toServer == INVALID_SOCKET) {
                printf("socket failed with error: %ld\n", WSAGetLastError());
                WSACleanup();
                return;
            }

            // Connect to server.
            iResult = connect(toServer, ptr->ai_addr, (int)ptr->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                closesocket(toServer);
                toServer = INVALID_SOCKET;
                continue;
            }
            break;
        }

    //WE connected to server socket here!
    freeaddrinfo(result);
    send(toServer,"Client connected!",25,0);

    //Listen to refresh new lobbies!
    char ch[5];
    int iRecResult;

    //socket names "toServer"
    while(1)
    {
        Sleep(200);
        if(message[0]=='-')
        {
            send(toServer,message.toStdString().c_str(),5,NULL);//nothing happening
        }
    }


    closesocket(toServer);
    WSACleanup();
}



/*
 *  this->ui->rating,
    this->ui->pl1,
    this->ui->score,
    this->ui->pl2,
    this->ui->details,
    this->ui->watch
 *
 * */
//Joining game by this user
void MainWindow::on_join_clicked()
{
    if(this->auth==false){
        return;
    }
    this->ui->join->hide();
    this->ui->score->show();
    this->ui->pl2->show();
    this->ui->details->show();
    this->ui->details->setText("Деталі");
    this->ui->watch->setText("Дивитись");
    this->ui->watch->show();
    this->ui->pl2->setText(player_name);
    ui->join->setDisabled(1);
    ui->join_2->setDisabled(1);
    ui->join_3->setDisabled(1);
    ui->join_4->setDisabled(1);
    ui->join_5->setDisabled(1);
    fillInfo(0);
    mstart("+3");//starting event
    clearlog();
    send(toServer,("          "+player_name).toStdString().c_str(),20,0);//name who joins
    Send(QString("          0"));//game id
    endm();
    gameid="01";
    gm->show();
    new std::thread(frameFormer,this);

    new std::thread(scoreChanged,this);
}

void MainWindow::on_join_2_clicked()
{
    if(this->auth==false){
        return;
    }
    this->ui->join_2->hide();
    this->ui->score_2->show();
    this->ui->pl2_2->show();
    this->ui->details_2->show();
    this->ui->watch_2->show();
    this->ui->pl2_2->setText(player_name);
    this->ui->details_2->setText("Деталі");
    this->ui->watch_2->setText("Дивитись");
    ui->join->setDisabled(1);
    ui->join_2->setDisabled(1);
    ui->join_3->setDisabled(1);
    ui->join_4->setDisabled(1);
    ui->join_5->setDisabled(1);
    fillInfo(1);
    mstart("+3");//starting event
    clearlog();
    send(toServer,("          "+player_name).toStdString().c_str(),20,0);//name who joins
    Send(QString("          1"));//game id
    endm();
    gameid="11";
    gm->show();
    new std::thread(frameFormer,this);
    new std::thread(scoreChanged,this);
}

void MainWindow::on_join_3_clicked()
{
    if(this->auth==false){
        return;
    }
    this->ui->join_3->hide();
    this->ui->score_3->show();
    this->ui->pl2_3->show();
    this->ui->details_3->show();
    this->ui->watch_3->show();
    this->ui->pl2_3->setText(player_name);
    this->ui->details_3->setText("Деталі");
    this->ui->watch_3->setText("Дивитись");
    ui->join->setDisabled(1);
    ui->join_2->setDisabled(1);
    ui->join_3->setDisabled(1);
    ui->join_4->setDisabled(1);
    ui->join_5->setDisabled(1);
    fillInfo(2);
    mstart("+3");//starting event
    clearlog();
    send(toServer,("          "+player_name).toStdString().c_str(),20,0);//name who joins
    Send(QString("          2"));//game id
    endm();
    gameid="21";
    gm->show();
    new std::thread(frameFormer,this);
    new std::thread(scoreChanged,this);
}

void MainWindow::on_join_4_clicked()
{
    if(this->auth==false){
        return;
    }
    this->ui->join_4->hide();
    this->ui->score_4->show();
    this->ui->pl2_4->show();
    this->ui->details_4->show();
    this->ui->watch_4->show();
    this->ui->pl2_4->setText(player_name);
    this->ui->details_4->setText("Деталі");
    this->ui->watch_4->setText("Дивитись");
    ui->join->setDisabled(1);
    ui->join_2->setDisabled(1);
    ui->join_3->setDisabled(1);
    ui->join_4->setDisabled(1);
    ui->join_5->setDisabled(1);
    fillInfo(3);
    mstart("+3");//starting event
    clearlog();
    send(toServer,("          "+player_name).toStdString().c_str(),20,0);//name who joins
    Send(QString("          3"));//game id
    gameid="31";
    gm->show();
    new std::thread(frameFormer,this);
    new std::thread(scoreChanged,this);
}

void MainWindow::on_join_5_clicked()
{
    if(this->auth==false){
        return;
    }
    this->ui->join_5->hide();
    this->ui->score_5->show();
    this->ui->pl2_5->show();
    this->ui->details_5->show();
    this->ui->watch_5->show();
    this->ui->pl2_5->setText(player_name);
    ui->join->setDisabled(1);
    ui->join_2->setDisabled(1);
    ui->join_3->setDisabled(1);
    ui->join_4->setDisabled(1);
    ui->join_5->setDisabled(1);
    fillInfo(4);
    mstart("+3");//starting event
    clearlog();
    send(toServer,("          "+player_name).toStdString().c_str(),20,0);//name who joins
    Send(QString("          4"));//game id
    gameid="41";
    gm->show();
    new std::thread(frameFormer,this);
    new std::thread(scoreChanged,this);

}

/*Label::Label(QWidget* parent, QLabel* par)
{
    this->setParent(parent);

    this->setPixmap(par->pixmap());
    this->setGeometry(par->geometry());
    par->hide();
    this->show();

}*/



void MainWindow::on_pl2_linkActivated(const QString &link)
{

}
void MainWindow::on_signal_add_clicked(){}

menuLabel::menuLabel(){}

void menuLabel::construct(QWidget* parent, QLabel* rep,MainWindow* mw,QString id)
{
    this->setParent(parent);
    this->setGeometry(rep->geometry());
    this->setPixmap(rep->pixmap());
    rep->hide();
    this->show();
    this->mw=mw;
    this->id=id;
}
//MENU ACTIONS
void menuLabel_clicked(menuLabel* obj)
{
    MainWindow* mm=obj->mw;
    QString btnName=obj->id;
    if(btnName=="add")
    {
        //Creating new game by this user
        obj->mw->createGame(obj->mw->player_name,obj->mw->ui->mmrt->text());
        obj->mw->add.hide();
        obj->mw->mm.hide();
        obj->mw->ui->join->setDisabled(1);
        obj->mw->ui->join_2->setDisabled(1);
        obj->mw->ui->join_3->setDisabled(1);
        obj->mw->ui->join_4->setDisabled(1);
        obj->mw->ui->join_5->setDisabled(1);
        mstart("+2");  //newly created battle
        clearlog();
        Send("          "+mm->player_name);
        Send("          "+mm->player_rating);
        endm();
        mm->gameid=QString::number(mm->gameCount-1)+"0";//(номер гри, сторона)
        new std::thread(start_effect,obj->mw);

    }
    if(btnName=="profile")
    {
        obj->mw->prf->show();
    }
}
bool menuLabel::event(QEvent *myEvent){
    {
        switch(myEvent->type())
        {
            case(QEvent :: MouseButtonRelease):   // Identify Mouse press Event
            {
                emit menuLabel_clicked(this);
                break;
            }
        }
        return QWidget::event(myEvent);
    }
}

void receiver(MainWindow* mm)
{
    //Message logic
    char recv_buf[15];
    char buffer[15];
    QString sms;
    char type;
    while(1)
    {
        Sleep(100);
        recv(toServer,recv_buf,15,0);
        type=recv_buf[0];
        sms=recv_buf;
        //mm->sd->ui->chat->setText(mm->sd->ui->chat->text()+QString("\n")+recv_buf);
        if(type!='\0'){
            mm->ui->db->setText(mm->ui->db->text()+"$"+sms);
        }

        switch(type)
        {
        case '1'://newcomer
        {
            //recv(toServer,recv_buf,10,0);
            mm->ui->online->setText(sms[1]);
            clearbuf(recv_buf,15);
            sms.clear();
            break;
        }
        case '2'://new battle created
        {
            char name[20];
            recv(toServer,name,15,0);
            recv(toServer,recv_buf,10,0);
            mm->createGame(name,recv_buf);
            break;
        }
        case '3'://someone joined any game
        {
            recv(toServer,recv_buf,15,0);//get name
            //show name
            recv(toServer,buffer,15,0);//get game id
            //show in number
            mm->fillInfo(int(buffer[0])-48,"0:0",recv_buf);//the game only starts for all
            if(buffer[0]==mm->gameid[0])
            {
                mm->gm->show();
                new std::thread(frameFormer,mm);
                new std::thread(scoreChanged,mm);
            }


            break;
        }
        case '4'://score has changed to anyone.
        {
            if(mm->gameid==QString(recv_buf[1])+recv_buf[2])//if this score is ours
            {
                mm->gm->opChoice=(int)recv_buf[3]-48;
                mm->gm->opSet();
                //mm->ui->db->setText("My Choice: "+QString::number(mm->gm->myChoice)+"\nOp choice now: "+QString::number(mm->gm->opChoice));

            }
            //anyways we need to change it in main window

            break;
        }

        case '5':
        {
            mm->scoreEditor(QString(sms[2])+sms[3],sms[1]);

            break;
        }

        case '6':
        {
            sms[0]=' ';
            char msgbuf[20];
            mm->sd->ui->chat->setText(mm->sd->ui->chat->text()+QString("\n")+sms);
            recv(toServer,msgbuf,20,0);//message
            mm->sd->ui->chat->setText(mm->sd->ui->chat->text()+QString(": ")+QString(msgbuf)+'\n');
            //mm->sd->ui->chat->setText(mm->sd->ui->chat->text()+QString("\n")+QString(recv_buf)+QString(": ")+QString(buffer));
            //recv(toServer,recv_buf,15,0);//playername
            /*recv(toServer,buffer,20,0);//message
            mm->ui->db->setText(mm->ui->db->text()+QString("$")+QString(buffer)+"$");

            //
            /*clearbuf(recv_buf,15);
            clearbuf(buffer,15);
            sms.clear();*/
            break;
        }


        }
    /**/}

        recv_buf[0]='\0';


}



void frameFormer(MainWindow* mm)
{
    int count=0;
    new std::thread(winner,mm->gm);
    int& choice=mm->gm->shared;
    while(1){
        Sleep(1000);
    if(choice!=-1)
    {
        if(count<=2){
            mstart(QString("+4"+(mm->gameid+QString::number(choice))).toStdString().c_str());
            endm();
        //send(toServer,QString("+4"+(mm->gameid+QString::number(choice))).toStdString().c_str(),7,0);
        }
        else{
            send(toServer,QString("          +4"+(mm->gameid+QString::number(choice))).toStdString().c_str(),7,0);
        }
        mm->gm->myChoice=choice;
        choice=-1;

        //mm->ui->db->setText("My Choice: "+QString::number(mm->gm->myChoice)+"\nOp choice now: "+QString::number(mm->gm->opChoice));
        //count++;
    }
    }

}

void scoreChanged(MainWindow* mm)
{
    int lastscore=0;
    while(1)
    {
        Sleep(2000);
        if(mm->gm->myscore>lastscore)
        {
            lastscore=mm->gm->myscore;
            QString scr="+5"+QString::number(lastscore)+mm->gameid;
            Sleep(1000);
            send(toServer,scr.toStdString().c_str(),10,0);
            scr="          +5"+QString::number(lastscore)+mm->gameid;
            send(toServer,scr.toStdString().c_str(),10,0);


        }



    }




}

void MainWindow::scoreEditor(QString gmid,QString score)
{
    QString scoreline;
    if(gmid[0]=='0')
    {
        if(gmid[1]=='0')
        {
            ui->score->setText(score+ui->score->text()[1]+ui->score->text()[2]);
        }
        else if(gmid[1]=='1')
        {
            ui->score->setText(QString(ui->score->text()[0])+ui->score->text()[1]+score);
        }
    }
    if(gmid[0]=='1')
    {
        if(gmid[1]=='0')
        {
            ui->score_2->setText(score+ui->score_2->text()[1]+ui->score_2->text()[2]);
        }
        else if(gmid[1]=='1')
        {
            ui->score_2->setText(QString(ui->score_2->text()[0])+ui->score_2->text()[1]+score);
        }
    }
    if(gmid[0]=='2')
    {
        if(gmid[1]=='0')
        {
            ui->score_3->setText(score+ui->score_3->text()[1]+ui->score_3->text()[2]);
        }
        else if(gmid[1]=='1')
        {
            ui->score_3->setText(QString(ui->score_3->text()[0])+ui->score_3->text()[1]+score);
        }
    }
    if(gmid[0]=='3')
    {
        if(gmid[1]=='0')
        {
            ui->score_4->setText(score+ui->score_4->text()[1]+ui->score_4->text()[2]);
        }
        else if(gmid[1]=='1')
        {
            ui->score_4->setText(QString(ui->score_4->text()[0])+ui->score_4->text()[1]+score);
        }
    }
    if(gmid[0]=='4')
    {
        if(gmid[1]=='0')
        {
            ui->score_5->setText(score+ui->score_5->text()[1]+ui->score_5->text()[2]);
        }
        else if(gmid[1]=='1')
        {
            ui->score_5->setText(QString(ui->score_5->text()[0])+ui->score_5->text()[1]+score);
        }
    }

}
bool muteflag=false;
void chatfollow(MainWindow* mm)
{
    while(1)
    {
        Sleep(10);
        if(muteflag){
        mm->sd->setGeometry(QRect(mm->mapToGlobal(QPoint(647,-10)),mm->sd->size()));}
    }

}
void chatPush(MainWindow* mm)
{
    int count=10;

    mm->sd->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    mm->sd->setWindowOpacity(0.2);
    mm->sd->resize(100,460);
    mm->sd->setGeometry(QRect(mm->mapToGlobal(QPoint(650,0)),mm->sd->size()));
    mm->sd->show();
    for(int i=0;i<23;i++)
    {
        Sleep(5);
        mm->sd->setGeometry(QRect(mm->mapToGlobal(QPoint(600+i*2,-10)),mm->sd->size()));
        mm->sd->resize(80+count,460);
        count+=5;
        mm->sd->setWindowOpacity(mm->sd->windowOpacity()+0.03);

    }
    mm->sd->setGeometry(QRect(mm->mapToGlobal(QPoint(645,-10)),mm->sd->size()));
    mm->sd->show();

    muteflag=true;

    new std::thread(chatfollow,mm);

}

void MainWindow::on_pushButton_clicked()
{
    new std::thread(chatPush,this);
    ui->pushButton->hide();
    ui->closeChat->show();
}
void chatShove(MainWindow* mm)
{
    //chatShove
    muteflag=false;
    int count=15;
    for(int i=0;i<30;i++)
    {
        mm->sd->resize(mm->sd->size().width()-count,460);
        count+=3;
        mm->sd->setWindowOpacity(mm->sd->windowOpacity()-0.02);
        Sleep(11);
    }
    mm->sd->hide();
    mm->sd->resize(100,460);
    mm->sd->setWindowOpacity(0.05);
    //delete chatfollower;
}
void MainWindow::on_closeChat_clicked()
{
    new std::thread(chatShove,this);
    ui->pushButton->show();
    ui->closeChat->hide();

}

void chatting(MainWindow* r)
{
    while(1)
    {
        Sleep(500);
        if(r->sd->text!="")
        {
            message="+";
            Sleep(500);
            if(r->sd->text=="shit" || r->sd->text=="sHit" || r->sd->text=="oh shit"
                    ||r->sd->text=="fuck"||r->sd->text=="bullshit")
            {
                r->sd->text="muted";
                Send(QString("+6"));
                Send(r->player_name);
                Send(QString("          ")+r->sd->text+'\0');
                r->sd->text="";
                message="-";
                return;
            }
            Send(QString("+6"));
            //clearlog();
            Send(r->player_name);
            //Send(QString("")+r->player_name+'\0');



            Send(QString("          ")+r->sd->text+'\0');
            r->sd->text="";
            message="-";

        }
    }
}


void moving_effect(MainWindow* mm, int casel)
{
    int adjust=0;
    int stance=1;
    int dir=0;
    int count=0;

    srand(time(NULL));
    int n=rand() %25+20;
    QLabel* e=mm->ui->effect1;
    QLabel* e2=mm->ui->effect1_2;
    QLabel* e3=mm->ui->effect1_3;
    QLabel* e4=mm->ui->effect1_4;
    QLabel* e5=mm->ui->effect1_5;
    e->show();
    e2->show();
    e3->show();
    e4->show();
    e5->show();
    for(int i=0;i<n;i+=2)
    {
        e->setGeometry(e->geometry().x(),
                                     e->geometry().y()+1,
                                     e->width(),
                                     e->height()
                                     );
        e2->setGeometry(e->geometry().x(),
                                     e2->geometry().y()+1,
                                     e2->width(),
                                     e2->height()
                                     );
        e3->setGeometry(e3->geometry().x(),
                                     e3->geometry().y()+2,
                                     e3->width(),
                                     e3->height()
                                     );
        e4->setGeometry(e4->geometry().x(),
                                     e4->geometry().y()+1,
                                     e4->width(),
                                     e4->height()
                                     );
        e5->setGeometry(e5->geometry().x(),
                                     e5->geometry().y()+2,
                                     e5->width(),
                                     e5->height()
                                     );
        if(count==0)
        {
            dir=rand()%2+1;
            count=rand()%3+1;
        }
        if(dir==1)
        {
            e->setGeometry(e->geometry().x()+1,
                                                 e->geometry().y(),
                                                 e->width(),
                                                 e->height()
                                                 );
            e2->setGeometry(e->geometry().x()-1,
                                                 e2->geometry().y(),
                                                 e2->width(),
                                                 e2->height()
                                                 );
            e3->setGeometry(e3->geometry().x()+1,
                                                 e3->geometry().y(),
                                                 e3->width(),
                                                 e3->height()
                                                 );
            e4->setGeometry(e4->geometry().x()-1,
                                                 e4->geometry().y(),
                                                 e4->width(),
                                                 e4->height()
                                                 );
            e5->setGeometry(e->geometry().x()+1,
                                                 e5->geometry().y(),
                                                 e5->width(),
                                                 e5->height()
                                                 );

        }
        else if(dir==2)
        {
            e->setGeometry(e->geometry().x()-1,
                                                 e->geometry().y(),
                                                 e->width(),
                                                 e->height()
                                                 );
            e2->setGeometry(e->geometry().x()+1,
                                                 e2->geometry().y(),
                                                 e2->width(),
                                                 e2->height()
                                                 );
            e3->setGeometry(e->geometry().x()+1,
                                                 e3->geometry().y(),
                                                 e3->width(),
                                                 e3->height()
                                                 );
            e4->setGeometry(e4->geometry().x()+1,
                                                 e4->geometry().y(),
                                                 e4->width(),
                                                 e4->height()
                                                 );
            e5->setGeometry(e5->geometry().x()-1,
                                                 e5->geometry().y(),
                                                 e5->width(),
                                                 e5->height()
                                                 );
        }
        count--;
        /*if(adjust==8)
        {
            stance=-1;
        }
        else if(adjust==-8)
        {
            stance=1;
        }


        e->setGeometry(e->geometry().x(),
                                     mm->ui->effect1_2->geometry().y()+2,
                                     mm->ui->effect1_2->width(),
                                     mm->ui->effect1_2->height()
                                     );
        e->setGeometry(e->geometry().x(),
                                     mm->ui->effect1_3->geometry().y()+2,
                                     mm->ui->effect1_3->width(),
                                     mm->ui->effect1_3->height()
                                     );

        e->setGeometry(mm->ui->effect1->geometry().x()+stance,
                                     mm->ui->effect1->geometry().y(),
                                     mm->ui->effect1->width(),
                                     mm->ui->effect1->height()
                                     );
        mm->ui->effect1_2->setGeometry(mm->ui->effect1_2->geometry().x()+stance,
                                     mm->ui->effect1_2->geometry().y(),
                                     mm->ui->effect1_2->width(),
                                     mm->ui->effect1_2->height()
                                     );
        /*mm->ui->effect1_3->setGeometry(mm->ui->effect1_3->geometry().x()+stance,
                                     mm->ui->effect1_3->geometry().y(),
                                     mm->ui->effect1_3->width(),
                                     mm->ui->effect1_3->height()
                                     );*/
        Sleep(5+i*3+dir);
    }
    e->hide();
    e2->hide();
    e3->hide();
    e4->hide();
    e5->hide();
}
void start_effect(MainWindow* mm)
{
    new std::thread(moving_effect,mm,1);
}

void MainWindow::on_pb_clicked()
{


}

void MainWindow::on_pushButton_3_clicked()
{
    system("start C:\\Users\\NtipreX\\Desktop\\Debug\\mplayer.exe");
}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->verticalSlider->isVisible())
    {
        ui->verticalSlider->hide();
    }
    else ui->verticalSlider->show();
}
