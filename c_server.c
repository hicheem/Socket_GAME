#include <stdio.h>
#include<string.h>
#include <winsock2.h>
#include<pthread.h>

#define BUFLEN 32	
#define PORT 8884


typedef struct client 
{
    SOCKET csock;
    SOCKADDR_IN csin;
    int x;
    int* final;
}client;

void* Client(void* param)
{
    client ct = *(client*)param;
    char buf[BUFLEN]="";
    int err,n,status=0;
    char nc='0';
    char message[BUFLEN];

    memset(buf,'\0', BUFLEN);
    //receiving name
    recv(ct.csock, buf, BUFLEN, 0);
    sprintf(message, "Welcome %s!\n",buf);
    if(send(ct.csock, message, strlen(message),0)!=SOCKET_ERROR)
    {
        memset(buf,'\0', BUFLEN);
        sprintf(message, "Choose a number in the range of:[0 - 10] to start game :\n");
        send(ct.csock, message, strlen(message),0);

        do
        {
            memset(buf,'\0', BUFLEN);
            //receiving
            recv(ct.csock, buf, BUFLEN, 0);
            n = atoi(buf);
            
            if(n==ct.x)
            {
                status=1;
                *(ct.final)=1;
                printf("%d",*ct.final);
                //sprintf(message, "You Won!\n");
            }
            else if(n<ct.x){
                sprintf(message, "more >>>>\n");
                }
            else if(n>ct.x){
                sprintf(message, "less <<<<\n");
                }
            if(n==ct.x && *(ct.final)==1)
                sprintf(message, "You Won!\n");
            else if(n!=ct.x && *(ct.final)==1)
                sprintf(message, "You Lose!\n");
            else if (n>10 || n<0)
                sprintf(message, "Please choose n in [1 10]\n");
            memset(buf,'\0', BUFLEN);
            send(ct.csock, message, strlen(message), 0);
            
            memset(buf,'\0', BUFLEN);
            if(status==1)
                sprintf(message, "good\n");
            else sprintf(message, "null\n");
            send(ct.csock, message, strlen(message), 0);

            memset(buf,'\0', BUFLEN);
            if(*(ct.final)==1)
                sprintf(message, "over\n");
            else sprintf(message, "null2\n");
            send(ct.csock, message, strlen(message), 0);
            

            
        } while (status!=1 && *(ct.final)!=1);
        
        
    }
    
        
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));
    int* final;
    SOCKET sock;
    SOCKADDR_IN sin;
    client ct[100];
    pthread_t thread;
    int sock_err,slen,i=0,p;
    char buf[BUFLEN];
    WSADATA wsa;
    slen = sizeof(ct[0].csin);
    int x = rand()%11;
    printf("The number is : %d\n",x);
    printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
    printf("Initialised.\n");

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock!=INVALID_SOCKET)
    {
        printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

        //Structure
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = htonl(INADDR_ANY);
        sin.sin_port = htons(PORT);
        sock_err = bind(sock,(SOCKADDR*)&sin,sizeof(sin));
        if(sock_err = listen(sock, 5) != SOCKET_ERROR)
        {
            printf("Listage du port %d...\n", PORT);
            while (1)
            {
                ct[i].csock = accept(sock,(SOCKADDR*)&ct[i].csin,&slen);                
                ct[i].x = x;
                ct[i].final = final;
                printf("Client %d has connected\n",i+1);
                p = pthread_create(&thread, NULL, Client, &ct[i]);
                i += 1;
            }
            
        }
    }
}