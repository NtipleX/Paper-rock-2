#include "paper2.h"
#include "ui_paper2.h"


fara::fara()
{

}
QString path="Resources";
MyLabel::MyLabel(Paper2 *papa_,short casel=-1,  const QString& text):QLabel(text,(QWidget*)papa_),casel(casel)
{
    papa=papa_;
}
Paper2::Paper2(QWidget* p)
    :QWidget(p)
    ,ui(new Ui::Paper2),shared(-1),myChoice(-1),opChoice(-1),myscore(0)
{
    ui->setupUi(this);




    QPixmap pm(path+"/pap.jpg");
    pm = pm.scaled(ui->case1->size(),Qt::KeepAspectRatio);  //загрузка картинок
    ui->case1->setPixmap(pm);

    pm.load(path+"/rock.png");
    pm=pm.scaled(ui->case2->size(),Qt::KeepAspectRatio);
    ui->case2->setPixmap(pm);

    pm.load(path+"/cut.jpg");
    pm=pm.scaled(ui->case3->size(),Qt::KeepAspectRatio);
    ui->case3->setPixmap(pm);

    pm.load(path+"/cup.jpg");
    pm=pm.scaled(ui->mycup->size(),Qt::KeepAspectRatio);
    ui->mycup->setPixmap(pm);
    ui->opcup->setPixmap(pm);

    static MyLabel lbl(this,1);         //свій клас, щоб не міняти старий лейбл - просто накладено
    lbl.setGeometry(50,230,70,70);

    static MyLabel lbl2(this,2);
    lbl2.setGeometry(210,225,70,70);

    static MyLabel lbl3(this,3);
    lbl3.setGeometry(110,340,70,70);
    ui->mycup->hide();
    ui->opcup->hide();
    //ui->lbl8->setText(path);



    /////////NETWORKING////////////

    //static std::thread client_networking(conn,this);    //creating network in another thread with another loop

    //finishing GUI by the main thread, next step for this is app main loop
    ////////////////////////////




    /*lbl1.setParent(this);
    lbl1.setText("Unknown");
    lbl1.setGeometry(5,5,50,15);
    lbl1.show();*/
}



void MyLabel::mouseReleaseEvent(QMouseEvent *ev)    //слот для відпускання миші по кастом лейблу
{
    switch(this->casel)     // пошук із об'єктів лейблів відповідного об'єкта який викликав подію
    {
    case 1:{
        papa->ui->case2->setStyleSheet("");
        papa->ui->case3->setStyleSheet("");
        papa->ui->case1->setStyleSheet("border: 1px solid gray;");
        QPixmap pm(path+"/pap.jpg");
        pm = pm.scaled(papa->ui->you->size(),Qt::KeepAspectRatio);
        papa->ui->you->setPixmap(pm);
        papa->shared=1;
        break;
    }
    case 2:{
        papa->ui->case1->setStyleSheet("");
        papa->ui->case3->setStyleSheet("");
        papa->ui->case2->setStyleSheet("border: 1px solid gray;");
        QPixmap pm(path+"/rock.png");
        pm = pm.scaled(papa->ui->you->size(),Qt::KeepAspectRatio);
        papa->ui->you->setPixmap(pm);
        papa->shared=2;
        break;
    }
    case 3:{
        papa->ui->case2->setStyleSheet("");
        papa->ui->case1->setStyleSheet("");
        papa->ui->case3->setStyleSheet("border: 1px solid gray;");
        QPixmap pm(path+"/cut.jpg");
        pm = pm.scaled(papa->ui->you->size(),Qt::KeepAspectRatio);
        papa->ui->you->setPixmap(pm);
        papa->shared=3;
        break;
    }
    }

}








Paper2::~Paper2()
{
    delete ui;
}










///////////////////////////////////////------------------------------

/*void conn(Paper2* wid)
{


    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET toServer=INVALID_SOCKET;

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
    std::thread receiving(receive_message,&toServer,wid);

    char ch[2] {' ','\0'};
    shared=-1;
    while(1)
    {
        if(shared>0)
        {
            ch[0]=shared+48;
            wid->setWindowTitle(ch);
            send(toServer, ch,2,0);
            shared=-1;
        }
        //waiting for GUI to response
    }

    closesocket(toServer);
    WSACleanup();
}*/



void receive_message(SOCKET* soc,Paper2* wid)
{
    char ch[5];
    int score=0;
    int iRecResult;


    while(1)
    {

        iRecResult=recv(*soc,ch,3,NULL);

        if(iRecResult>0 ){
                    if (*ch=='3')
                    {
                        QPixmap pm(path+"/unknown.png");
                        pm=pm.scaled(wid->ui->lblop->size(),Qt::KeepAspectRatio);
                        wid->ui->lblop->setPixmap(pm);
                    }
                    else if(*ch=='1'){
                        determine(wid);
                        score = wid->ui->myscore->text().toInt()+1;
                        wid->ui->myscore->setText(QString((char)(score+48)));
                        wid->ui->mycup->show();
                        Sleep(2700);
                        wid->ui->case1->setStyleSheet("");
                        wid->ui->case2->setStyleSheet("");
                        wid->ui->case3->setStyleSheet("");
                        wid->ui->you->setPixmap(QPixmap());
                        wid->ui->lblop->setPixmap(QPixmap());
                        Sleep(700);
                        wid->ui->mycup->hide();

                    }
                    else if(*ch=='0')
                    {
                        determine(wid);
                        score = wid->ui->opscore->text().toInt()+1;
                        wid->ui->opscore->setText(QString((char)(score+48)));
                        wid->ui->opcup->show();
                        Sleep(2700);
                        wid->ui->case1->setStyleSheet("");
                        wid->ui->case2->setStyleSheet("");
                        wid->ui->case3->setStyleSheet("");
                        wid->ui->you->setPixmap(QPixmap());
                        wid->ui->lblop->setPixmap(QPixmap());
                        Sleep(700);
                        wid->ui->opcup->hide();

                    }
                    else if(*ch=='2')
                    {
                        determine(wid);
                        Sleep(1300);
                        wid->ui->case1->setStyleSheet("");
                        wid->ui->case2->setStyleSheet("");
                        wid->ui->case3->setStyleSheet("");
                        wid->ui->you->setPixmap(QPixmap());
                        wid->ui->lblop->setPixmap(QPixmap());
                    }
                    //wid->ui->myscore->setText(wid->ui->myscore->text()+"t");
                }


        //wid->lbl1.setText(ch);
        /*if(*ch=='1')
        {
            wid->lbl1.setText("You winner!");
        }
        else if (*ch=='0')
        {
            wid->lbl1.setText("You lose!");
        }*/
        //Let GUI know about it.
    }
}

void determine(Paper2* wid)//допоміжна функція для функції receive_message
{
    QPixmap pm;
    wid->ui->lblop->setPixmap(pm);

    if(wid->opChoice=='1') pm.load(path+"/pap.jpg");
    else if(wid->opChoice=='2') pm.load(path+"/rock.png");
    else if(wid->opChoice=='3') pm.load(path+"/cut.jpg");

    pm=pm.scaled(wid->ui->lblop->size(),Qt::KeepAspectRatio);
    wid->ui->lblop->setPixmap(pm);

}


void Paper2::opSet(int choice)
{
    QPixmap pm;
    ui->lblop->setPixmap(pm);
    if(choice==0)
    {
        pm.load(path+"/unknown.png");
    }
    else if(choice==1)
    {
        pm.load(path+"/pap.jpg");
    }
    else if(choice==2)
    {
        pm.load(path+"/rock.png");
    }
    else if(choice==3)
    {
        pm.load(path+"/cut.jpg");
    }
    pm=pm.scaled(ui->lblop->size(),Qt::KeepAspectRatio);
    ui->lblop->setPixmap(pm);
}
char who_win(int a, int b)
{

    if (a == 1 && b == 2) return '1';
    else if (a == 1 && b == 3) return '2';
    else if (a == 1 && b == 1) return '0';

    if (a == 2 && b == 1) return '2';
    else if (a == 2 && b == 3) return '1';
    else if (a == 2 && b == 2) return '0';

    if (a == 3 && b == 1) return '1';
    else if (a == 3 && b == 2) return '2';
    else if (a == 3 && b == 3) return '0';

}
 void winner(Paper2* wid)
{
     while(1){
         Sleep(1000);
         //wid->setWindowTitle("My:"+QString::number(wid->myChoice)+"Op:"+QString::number(wid->opChoice));
    if(wid->myChoice>0 && wid->opChoice>0)
    {
        QString g(who_win(wid->myChoice,wid->opChoice));

        if(g=='1'){
        int score = wid->ui->myscore->text().toInt()+1;
        wid->ui->myscore->setText(QString((char)(score+48)));
        wid->ui->mycup->show();
        wid->opSet(wid->opChoice);
        Sleep(2700);
        wid->ui->case1->setStyleSheet("");
        wid->ui->case2->setStyleSheet("");
        wid->ui->case3->setStyleSheet("");
        wid->ui->you->setPixmap(QPixmap());
        wid->ui->lblop->setPixmap(QPixmap());
        Sleep(700);
        wid->ui->mycup->hide();
        wid->myChoice=-1;
        wid->opChoice=-1;
        wid->myscore++;
        }
        else if(g=='2')
        {
            int score = wid->ui->opscore->text().toInt()+1;
            wid->ui->opscore->setText(QString((char)(score+48)));
            wid->ui->opcup->show();
            wid->opSet(wid->opChoice);
            Sleep(2700);
            wid->ui->case1->setStyleSheet("");
            wid->ui->case2->setStyleSheet("");
            wid->ui->case3->setStyleSheet("");
            wid->ui->you->setPixmap(QPixmap());
            wid->ui->lblop->setPixmap(QPixmap());
            Sleep(700);
            wid->ui->opcup->hide();

            wid->myChoice=-1;
            wid->opChoice=-1;
        }
        else if(g=='0')
        {
            int score = wid->ui->opscore->text().toInt()+1;
            wid->ui->opscore->setText(QString((char)(score+48)));
            wid->ui->opcup->show();
            wid->opSet(wid->opChoice);
            Sleep(2700);
            wid->ui->case1->setStyleSheet("");
            wid->ui->case2->setStyleSheet("");
            wid->ui->case3->setStyleSheet("");
            wid->ui->you->setPixmap(QPixmap());
            wid->ui->lblop->setPixmap(QPixmap());
            Sleep(700);
            wid->ui->opcup->hide();

            wid->myChoice=-1;
            wid->opChoice=-1;
        }
    }

     }
}
