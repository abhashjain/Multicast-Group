#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

int main(int argc, char *argv[])
{
int sockfd = 0;
char sendBuff[1024];
struct sockaddr_in serv_addr;
int i=0;

if(argc != 2)
{
    printf("\n Usage: %s <ip of server> \n",argv[0]);
    return 1;
} 

if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
{
    printf("\n Error : Could not create socket \n");
    return 1;
} 

memset(&serv_addr, '0', sizeof(serv_addr)); 

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(5000); 

if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
{
    printf("\n inet_pton error occured\n");
    return 1;
} 

if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
{
   printf("\n Error : Connect Failed \n");
   return 1;
}

do{
  memset(sendBuff, '\0', sizeof(sendBuff));
  sprintf(sendBuff, "Server got This is line %d", i);
  send(sockfd, sendBuff, strlen(sendBuff), 0);
  memset(sendBuff, '\0', sizeof(sendBuff));
  recv(sockfd, sendBuff, sizeof(sendBuff),0);
  printf( "%s\n", sendBuff);
  //sleep(5);

}while(++i<2);




return 0;
}

