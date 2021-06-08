#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <string.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


void receive(SOCKET soc,char);
void prim_recv(SOCKET soc);
void accept_connections(SOCKET);
void Recv(SOCKET, char*&);
void forward(char*);
void recvlog(SOCKET);
SOCKET ClientSocket = INVALID_SOCKET;
SOCKET ClientSocket2 = INVALID_SOCKET;
SOCKET sockets[50];
int online = 0;


int __cdecl main(void)
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    for (int i = 0; i < 50; i++)
    {
        sockets[i] = INVALID_SOCKET;
    }

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    char sndbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    char h;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    //freeaddrinfo(result);
    static std::thread accept_con(accept_connections, ListenSocket);
    
    
        //send(ClientSocket, "12", 150, 0);
        /*iResult = listen(ListenSocket, SOMAXCONN);                              //######
        if (iResult == SOCKET_ERROR) {
            printf("listen failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        ClientSocket2 = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }
        recv(ClientSocket2, recvbuf, recvbuflen, 0);
        std::cout << recvbuf << std::endl;
        // No longer need server socket
        //closesocket(ListenSocket);

        */


        /*recv(ClientSocket2, recvbuf, recvbuflen, 0);
        std::cout << recvbuf<<std::endl;
        //send(ClientSocket, "You are connected to me!\n", 150, 0);*/

        //char* msg[5];
        int res = 0;
        while (1) {
            for (int i = 0; i < 40; ++i) {
                if (sockets[i] == INVALID_SOCKET) { continue; }
                SOCKET client=INVALID_SOCKET;
                char msg1[20];
                char msg2[20];
                char msg3[20];
                res = recv(sockets[i], msg1, 10, NULL);
                if (msg1[0] == '+')
                {
                    std::cout <<"MESSAGE:"<< msg1 << std::endl;
                    msg1[0] = 'N';
                    std::cout << msg1 << i <<':'<<' ';
                    //Message logic
                    switch (msg1[1])
                    {
                    case '2'://Newly created battle
                    {
                        client = sockets[i];
                        std::cout << "CASE 2\n";
                        for (int l = 0; l < 5; l++) {
                            recv(sockets[i], msg2, 20, 0);//get name of joiner
                            //std::cout << "CLEARING:" << msg2 << std::endl;
                            Sleep(300);
                        }
                        recv(sockets[i], msg2, 20, NULL);//get name of the creator
                        recv(sockets[i], msg3, 20, NULL);//get rating
                        std::cout << "Newly created battle by "<<msg2 <<" with rating: "<<msg3<<'\n';
                        for (int j = 0; j < online; j++)
                        {
                            if (j == i) { continue;}
                            send(sockets[j], "2",2, 0);
                            send(sockets[j], msg2,15, 0);
                            send(sockets[j], msg3,15, 0);
                        }
                        break;
                    }
                    case '3'://joining battle
                    {
                        client = sockets[i];
                        std::cout << "CASE 3\n";
                        for(int l=0;l<5;l++) {
                            recv(sockets[i], msg2, 20, 0);//get name of joiner
                            //std::cout<<"CLEARING:"<< msg2<<std::endl;
                            Sleep(300);
                        }
                        recv(sockets[i], msg2, 20, 0);//get name of joiner
                        recv(sockets[i], msg3, 20, 0);//get game id of joiner
                        std::cout << "Joining battle ";
                        std::cout << msg2;
                        std::cout << " game id" << ' '<< msg3<<std::endl;
                        for (int j = 0; j < online; j++)
                        {
                            if (j == i) { continue; }
                            send(sockets[j], "3", 2, 0);    //send event
                            send(sockets[j], msg2, 15, 0);//send name
                            send(sockets[j], msg3, 15, 0);//send game id

                        }
                        break;
                    }
                    case '4':
                    {
                        std::cout << msg1<<std::endl;
                        msg2[0] = '4';
                        msg2[1] = msg1[2];
                        if (msg1[3] == '1') { msg2[2] = '0'; }
                        else { msg2[2] = '1'; }
                        msg2[3] = msg1[4];
                        msg2[4] = '\0';//*(4012) 4 event; 01 gameid; 2 message
                        //forming message completed, sending
                        for (int j = 0; j < online; j++)
                        {
                            if (j == i) { continue; }
                            send(sockets[j], msg2, 5, 0);    //send event and message together
                            
                        }
                        break;

                    }
                    case '5':
                    {
                        //"+5" + QString::number(lastscore) + mm->gameid;
                        std::cout << "CASE 5:" << msg1 << std::endl;
                        msg2[0] = msg1[1];
                        msg2[1] = msg1[2];
                        msg2[2] = msg1[3];
                        msg2[3] = msg1[4];
                        msg2[4] = '\0';
                        for (int j = 0; j < online; j++)
                        {
                            send(sockets[j], msg2, 10, 0);
                        }
                    }
                    case '6':
                    {
                        Sleep(100);
                        std::cout << "CASE 6:" << msg1 << std::endl;
                        /*for (int l = 0; l < 5; l++) {
                            recv(sockets[i], msg1, 20, 0);
                            std::cout<< msg1 << std::endl;
                            Sleep(100);
                        }*/
                        //recvlog(sockets[i]);
                        recv(sockets[i],msg1,10,0);//name
                        recv(sockets[i],msg1,10,0);//name

                        
                        
                        recv(sockets[i], msg2, 20, 0);
                        recv(sockets[i], msg2, 20, 0);
                        std::cout << "RECEIVED:" << msg1<<':'<<msg2<<'$'<<std::endl;
                        std::string a = "6";
                        a += msg1;
                        //forward(msg2);
                        for (int j = 0; j < online; j++)
                        {
                            std::cout << "SENDING:" << a << ':' << msg2 <<'$'<< std::endl;// << '|' << msg2 <<'$'<< std::endl;
                            send(sockets[j],a.c_str(), 15, 0);
                            send(sockets[j], msg2, 20, 0);
                            //send(sockets[j], msg1, 15, 0);
                            //send(sockets[j], msg2, 20, 0);
                        }
                    }
                    /*finally:
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            delete msg[i];
                        }
                        break;
                    }*/



                    }

                }
                else
                {
                    std::cout << msg1 << std::endl;
                    //delete msg[0];
                }

            }
        }
        

        /*std::thread receive_thread(receive, ClientSocket,'1');
        std::thread receive_thread2(receive, ClientSocket2,'2');
        */


        /*while (1)
        {
            std::cin.getline(sndbuf, recvbuflen);
            send(ClientSocket, sndbuf, recvbuflen, 0);
            send(ClientSocket2, sndbuf, recvbuflen, 0);
        }*/

        std::cin >> h;










        // shutdown the connection since we're done
        for (int i = 0; i < 50; i++)
        {

            iResult = shutdown(sockets[i], SD_SEND);
            if (iResult == SOCKET_ERROR) {
                printf("shutdown failed with error: %d\n", WSAGetLastError());
                closesocket(sockets[i]);
                WSACleanup();
                return 1;
            }

            // cleanup
            closesocket(sockets[i]);
        }
        WSACleanup();

        return 0;
    }

int reply1 = -1;
int reply2 = -1;

void Opsend(char, char, int, int);
/*void receive(SOCKET soc, char player)
{
    char recvbuf[DEFAULT_BUFLEN];
    int choose;
    int iResult;
    
    while (1) {
        iResult = recv(soc, recvbuf, DEFAULT_BUFLEN, 0);
        if (iResult > 0) {
            choose = (int)recvbuf[0] - 48;
            std::cout << "Player " << player << " has choosen: " << choose << std::endl;
            if (player == '1') {
                if (reply2 < 0) //Only one player has made a choise
                {
                    reply1 = choose;
                    Opsend(player, '3',-1,-1);//let know other about making choise
                }
                else if (reply2 > 0)
                {
                    //calculations and sending.
                    reply1 = choose;
                    int answ = who_win(reply1, reply2);
                    if (answ == '1') {
                        std::cout << "Player " << player << " win!\n\n";
                        Opsend(player, answ,reply1,reply2);
                    }
                    else if (answ == '0') {
                        std::cout << "Tie!\n\n";
                        Opsend(player, answ,reply1,reply2);
                        
                    }
                    else if (answ == '2') {
                        std::cout << "Player " << (player == '1' ? '2' : '1') << " win!\n\n";
                        Opsend(player, answ,reply1,reply2);
                    }

                    reply1 = -1;
                    reply2 = -1;
                    continue;
                }
            }
            else if (player == '2') {
                if (reply1 < 0)
                {
                    reply2 = choose;
                    Opsend(player, '3',-1,-1);
                }
                else if (reply1 > 0)
                {
                    reply2 = choose;
                    //calculations and sending.
                    int answ = who_win(reply2, reply1);
                    if (answ == '1') {
                        std::cout << "Player " << player << " win!\n\n";
                        Opsend(player, answ,reply1,reply2);
                    }
                    else if (answ == '0') {
                        std::cout << "Tie!\n\n";
                        Opsend(player, answ, reply1,reply2);
                    }
                    else if (answ == '2') {
                        std::cout << "Player " << (player == '1' ? '2' : '1') << " win!\n\n";
                        Opsend(player, answ, reply1,reply2);
                    }

                    reply1 = -1;
                    reply2 = -1;
                    continue;
                }
            }
        }

        else if (iResult == 0) std::cout << "Connection clossing...\n";
        else
        {
            printf("recv failed with error: disconnect\n");//WSAGetLastError());
            closesocket(soc);
            WSACleanup();
            return;
        }
    }
}
*/


void Opsend(char player,char result,int pl1,int pl2)
{
    char goodres = '1';
    char badres = '0';
    char tie = '2';
    char ready = '3';
    char opch1 = pl1+48;
    char opch2 = pl2 + 48;

    //send(ClientSocket2, &opch, 1, 0);
    if (player == '1' && result == '3')
    {
        send(ClientSocket2, &ready, 1, 0);
        return;
    }
    else if (player == '2' && result == '3')
    {
        send(ClientSocket, &ready, 1, 0);
        return;
    }
    else if (player == '1' && result=='1')
    {
        send(ClientSocket, &goodres, 1, 0);
        send(ClientSocket2, &badres, 1, 0);
    }
    else if (player == '1' && result == '2')
    {
        send(ClientSocket, &badres, 1, 0);
        send(ClientSocket2, &goodres, 1, 0);
    }
    else if (result == '0')
    {
        send(ClientSocket, &tie, 1, 0);
        send(ClientSocket2, &tie, 1, 0);
    }
    else if (player == '2' && result == '1')
    {
        send(ClientSocket, &badres, 1, 0);
        send(ClientSocket2, &goodres, 1, 0);
    }
    else if (player == '2' && result == '2')
    {
        send(ClientSocket, &goodres, 1, 0);
        send(ClientSocket2, &badres, 1, 0);
    }

    send(ClientSocket, &opch2, 1, 0);
    send(ClientSocket2, &opch1, 1, 0);
}

//######################################################
//Задача - виводити на екран те що вибрав клієнт.
void prim_recv(SOCKET soc)
{
    char buf[DEFAULT_BUFLEN];
    while (1){
        recv(soc, buf, DEFAULT_BUFLEN, NULL);
        std::cout << buf<<std::endl;
    }

}



void accept_connections(SOCKET ListenSocket) {
    char recvbuf[DEFAULT_BUFLEN];
    char sndbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    while (1) {
        int iResult = listen(ListenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR) {
            printf("listen failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
        }
        // Accept a client socket
        char pt[5];
        std::string ms="1";
        for (int i = 0; i < 50; i++) {
            if (sockets[i] == INVALID_SOCKET) {
                
                sockets[i] = accept(ListenSocket, NULL, NULL);
                if (sockets[i] == INVALID_SOCKET) {
                    printf("accept failed with error: %d\n", WSAGetLastError());
                    continue;
                }
                recv(sockets[i], recvbuf, recvbuflen, 0);
                std::cout << recvbuf << std::endl;
                online++;
                _itoa_s(online, pt, 10);
                ms += pt;
                std::cout << "SENDING:" << ms<<std::endl;
                for (int j = 0; j <= 20; j++)
                {
                    send(sockets[j], ms.c_str(), 5, 0);
                }
                ms = "1";
            }
        }
    }
}
void Recv(SOCKET s, char*& buf)
{
    do {
        recv(s, buf, 20, 0);
    } while (buf[0] == '-' || buf[0] == '\0');
}
void forward(char*b)
{
    for (int i = 9; i !=-1; i--)
    {
        b[i + 5] = b[i];
    }
}
void recvlog(SOCKET s)
{
    char buf[20];
    for (int i = 0; i < 4; i++) {
        recv(s, buf, 20, 0);
    }
}