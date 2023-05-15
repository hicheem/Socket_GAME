#include <stdio.h>
#include<string.h>
#include <winsock2.h>

#define BUFLEN 32	
#define PORT 8884

int main(int argc, char const *argv[])
{
    SOCKET csock;
    SOCKADDR_IN sin;
    char buf[BUFLEN]="",nc,f[BUFLEN];
    int sock_err,slen,n,status;
    WSADATA wsa;
    char name[BUFLEN];

    printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

    csock = socket(AF_INET, SOCK_STREAM, 0);
    if(csock!=INVALID_SOCKET)
    {
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = inet_addr("127.0.0.1");
        sin.sin_port = htons(PORT);

        if(connect(csock, (SOCKADDR*)&sin, sizeof(sin))!=SOCKET_ERROR)
        {
            //printf("Connection a %s sur le port %d\n\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
            memset(buf,'\0', BUFLEN);
            printf("What is your name : ");
            scanf("%s",&name);
            send(csock, name, BUFLEN, 0);
            if(recv(csock, buf, BUFLEN, 0)!=SOCKET_ERROR)
            {
                printf("%s\n",buf);
                recv(csock, buf, BUFLEN, 0);
                printf("%s",buf);
                recv(csock, buf, BUFLEN, 0);
                printf("%s\n",buf);
                //sending 
                do
                {
                    scanf("%d",&n);
                    nc = n+'0';
                    send(csock, &nc, BUFLEN, 0);
                    
                    memset(buf,'\0',BUFLEN);
                    recv(csock, buf, BUFLEN, 0);
                    printf("\n%s\n",buf);
                    
                    memset(buf,'\0',BUFLEN);
                    recv(csock, buf, BUFLEN, 0);

                    //memset(buf,'\0',BUFLEN);
                    // memset(f,'\0',BUFLEN);
                    //recv(csock, buf, BUFLEN, 0);
                    
                    //printf("buf : %s",buf);
                
                }while(strcmp(buf, "good\nover")!=0 && strcmp(buf, "over\nnull2")!=0);
                
                
                
            }
        }
    
    }
}
