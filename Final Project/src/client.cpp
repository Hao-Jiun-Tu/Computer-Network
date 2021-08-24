#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef PORT
#define PORT 1234
#endif

#ifndef IP_Address
#define IP_Address "127.0.0.1"
#endif

using namespace std;

int main(){

    cout << "IP_A = " << IP_Address << endl;
    cout << "PORT = " << PORT << endl;

    char message_send[100], message_recv[100];
    struct sockaddr_in serv_addr;
    int sockfd;

    //setup the server address
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(IP_Address);
    
    //connect to the server
    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    while(1){
        
        //clear buffer before reading 
        memset(message_recv, '\0', sizeof(message_recv)); 
        read(sockfd, message_recv, 100);
        cout << message_recv;
        cin >> message_send;
        write(sockfd, message_send, strlen(message_send)); //write 1(DNS) | 2(QUERY) | 3(QUIT) | ELSE                
        if(!strcmp(message_send, "3"))
            break;

        //clear buffer before reading 
        memset(message_recv, '\0', sizeof(message_recv)); 
        read(sockfd, message_recv, 100); //read ("Input URL address : " | "Input student ID : " | X | "Wrong command")
        cout << message_recv;
        cin >> message_send;
        write(sockfd, message_send, strlen(message_send)); //write (URL | student ID)
    
    }
    close(sockfd);
    return 0;
}

