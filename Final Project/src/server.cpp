#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 1234

using namespace std;

int main(){

    int sockfd, streamfd;
    int cli_len, status;

    char *IP_addr; 
    char message_send[100], message_recv[100];
    char fstr[100], data[100][100]; //to store data in query.txt 
    int  data_size; //data size in query.txt
    bool EMAIL_finded;
    fstream infile;

    struct sockaddr_in serv_addr, cli_addr;
    struct hostent *HostEntry;
    struct in_addr IP_ADDR;

    //Initialize socket structure
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if(sockfd < 0){
        cout << "The socket not opened" << endl;
        exit(1);
    } else
        cout << "The socket opened successfully" << endl;
    
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        cout << "ERROR on binding" << endl;
        exit(1);
    }

    listen(sockfd, 10);
    cli_len = sizeof(cli_addr);

    //Read the data in query.txt
    data_size = 0;
    infile.open("query.txt", ios::in);
    while(infile >> fstr){
        strcpy(data[data_size++], fstr);
    }
    infile.close();

    while(1){
        cout << "Waiting for connection..." << endl;            
        streamfd = accept(sockfd, (struct sockaddr*)&cli_addr,(socklen_t*)&cli_len);
         
        memset(message_send, '\0', sizeof(message_send)); 
        while(1){
            strcat(message_send ,"What's your requirement? 1.DNS 2.QUERY 3.QUIT : ");
            write(streamfd, message_send, strlen(message_send));
            
            //Clear message buffer before reading
            memset(message_recv, '\0', sizeof(message_recv)); 
            read(streamfd, message_recv, 100);
            
            if(!strcmp(message_recv, "1")){
                cout << "String from client : DNS" << endl;
                strcpy(message_send ,"Input URL address : ");
                write(streamfd, message_send, strlen(message_send));
                
                //Clear message buffer before reading
                memset(message_recv, '\0', sizeof(message_recv)); 
                read(streamfd, message_recv, 100); // URL address
                
                int i = 0;
                HostEntry = gethostbyname(message_recv);
                if(HostEntry){
                    while(HostEntry->h_addr_list[i] != 0){
                        IP_ADDR.s_addr = *(u_long*)HostEntry->h_addr_list[i++];
                    }
                    strcpy(message_send, "Address get from domain name : ");
                    strcat(message_send, inet_ntoa(IP_ADDR));
                    strcat(message_send, "\n\n");
                } else
                    strcpy(message_send, "Address get from domain name : No such URL address\n\n");
                
            } else if(!strcmp(message_recv, "2")){
                cout << "String from client : QUERY" << endl;
                strcpy(message_send ,"Input student ID : ");
                write(streamfd, message_send, strlen(message_send));
                
                //Clear message buffer before reading
                memset(message_recv, '\0', sizeof(message_recv)); 
                read(streamfd, message_recv, 100); // student ID
                
                EMAIL_finded = false;
                int i = 0;
                while(!EMAIL_finded){
                    if(!strcmp(data[i++], message_recv)){
                        EMAIL_finded = true;
                        strcpy(message_send, "Email get from server : ");
                        strcat(message_send, data[i]);
                        strcat(message_send, "\n\n");
                        break;
                    }
                    if(i > data_size)
                        break;
                }
                if(!EMAIL_finded)
                    strcpy(message_send, "Email get from server : No such student ID\n\n");
            } else if(!strcmp(message_recv, "3")){
                cout << "String from client : QUIT" << endl;
                break;
            } else {
                cout << "Wrong command!" << endl;
                strcpy(message_send ,"Wrong command, number should be 1 to 3\n\n");
            } 
        }
        close(streamfd);
    }
    return 0;
}

