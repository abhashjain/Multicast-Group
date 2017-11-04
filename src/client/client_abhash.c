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
#include <pthread.h>

#include "../includes/logger.h"


#define PORT 4006
#define MAX_ARRAY_ELEMENTS 100000

typedef enum _operation
{
    JOIN = 1,
    DELETE = 2,
    RESULT = 3
}OPERATION;

typedef struct _server_details
{
    char ip_addr[16];
    int sockFd;
}SERVER_DETAILS;

static char ser_ip_addr[16];
static int sockFd = 0;

void parse_input(char* buf);
void my_itoa(int num, char *str)
{
    if(str == NULL)
    {
        return NULL;
    }
    sprintf(str, "%d", num);
}

char *prepare_buffer(int *array, int num_of_elements)
{
    char str_num[5];
    long indx = 0;
    char *buffer = NULL;
    
    if(NULL != array)
    {
        printf("prepare_buffer num_of_elements = %d\n",num_of_elements);
        buffer = (char *)malloc((sizeof(int) * num_of_elements));
        if(buffer != NULL)
        {
            printf("Allocation is success\n");
	    strcat(buffer,"R");
            for(indx = 0;indx < num_of_elements;indx++)
            {
                my_itoa(array[indx],str_num);
                strcat(buffer, str_num);
                strcat(buffer, " ");
            }
        }
        
        printf("formed buffer is %s\n",buffer);
    }
    return buffer;
}
void sendTask(void *data)
{
    int op = 0;
    char buffer[1024];
    int join_flag = 0;
    SERVER_DETAILS *server_details = (SERVER_DETAILS *)data;
    while(1){
        if(join_flag == 0){
            printf("****************************************\n");
            printf("Enter the opeartion\n");
            printf("1 - To join\n");
            printf("****************************************\n");
        } else{
            printf("****************************************\n");
            printf("Enter the opeartion\n");
            printf("2 - To delete\n");
            printf("****************************************\n");
        }
        scanf("%d",&op);
        if(op == 1){
            join_flag = 1;
        } else {
            join_flag = 0;
        }
        sendMessage(op, server_details->ip_addr, buffer,server_details->sockFd);
    }
}

void recvTask(void *data)
{
    char receive_buff[1024];
    SERVER_DETAILS *server_details = (SERVER_DETAILS *)data;
    printf("Inside recvTask\n");
    while(1)
    {
        memset(receive_buff, '\0', sizeof(receive_buff));
	printf("revcvcvcvc %d\n",server_details->sockFd);
        recv(server_details->sockFd, receive_buff, sizeof(receive_buff),0);
        printf("%s\n",receive_buff);
        if(strcmp(receive_buff,"JOINED")==0)
        {
           printf("In PerformTask JOINED\n");
        }
        else
        {
            printf("Client Received some work\n");

            printf("Data is : %s\n", receive_buff);
	    parse_input(receive_buff);
        }
    }
}


#if 0
void JoinToGroup(char *ip_addr, char capability)
{
    int sockfd = 0;
    char sendBuff[1024];
    struct sockaddr_in serv_addr;
    int i=0;
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return;
    }

    printf("GSH : PerformTask 4444 sockfd = %d\n",sockfd);

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 
    
    if(inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return;
    } 
    
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return;
    }

    memset(sendBuff, '\0', sizeof(sendBuff));
    sprintf(sendBuff, "%c", capability);
    send(sockfd, sendBuff, strlen(sendBuff), 0);
    memset(sendBuff, '\0', sizeof(sendBuff));
    recv(sockfd, sendBuff, sizeof(sendBuff),0);
    printf("%s\n",sendBuff);
    if(strcmp(sendBuff,"JOINED")!=0)
    {
      printf("Client could not joined");
      return;
    }     
}

void ExitFromGroup()
{
    //ToDo
}

void JoinOrExit(){
    int choice;
    char capability;
    char ser_ip_addr[16];
    do{
	printf("######################\n");
	printf("Enter your choice\n");
	printf("1. Join to group\n");
	printf("2. Exit from group\n");
	printf("######################\n");
	scanf("%d",&choice);
    
	switch(choice){
		case 1 :
            //printf("Enter capability of the client\n");
            //capability = getchar();
            capability = 'S';
            printf("Enter the server IP Address\n");
            scanf("%s",ser_ip_addr);
		    JoinToGroup(ser_ip_addr, capability);
		    break;
		case 2:
            ExitFromGroup();
		    break;
		default:
		    break;	
	}		
    }while(1);
}

void PerformTask()
{
    //to do
    int sockfd = 0;
    struct sockaddr_in serv_addr;
    int i=0;
    char receive_buff[1024];
    char ser_ip_addr[16] = "127.0.0.1";

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 

    printf("GSH : PerformTask 1111\n");

    do{
        printf("GSH : PerformTask 3333 sockfd = %d\n",sockfd);

        memset(receive_buff, '\0', sizeof(receive_buff));
        recv(sockfd, receive_buff, sizeof(receive_buff),0);
        printf("%s\n",receive_buff);
        if(strcmp(receive_buff,"JOINED")==0)
        {
           printf("In PerformTask JOINED\n");
        }
        else
        {
            printf("Client Received some work\n");

            printf("Data is : %s\n", receive_buff);

        }

        sleep(60);
    }while(1);
    return;    
}

#endif
int main(int argc, char *argv[])
{
    SERVER_DETAILS server_details;

    pthread_t thread1,thread2;
    int  iret1,iret2;

    printf("Enter the server IP Address\n");
    scanf("%s",ser_ip_addr);
    sockFd = connectToServer(ser_ip_addr);
    printf("socketfd %d \n",sockFd);
    if(-1 == sockFd)
    {
        printf("Coonection failed - Some serious problem\n");
        exit(1);
    }

    memcpy(server_details.ip_addr,ser_ip_addr,sizeof(server_details.ip_addr));
    server_details.sockFd = sockFd;

    iret1 = pthread_create( &thread1, NULL,sendTask , (void *)&server_details);
    iret2 = pthread_create( &thread2, NULL,recvTask , (void *)&server_details);
    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
    printf("Thread 2 returns: %d\n",iret2);
    printf("Thread 1 returns: %d\n",iret1);
    
}


int * sortNumbers(int *array, int num_of_elements)
{
    int indx_i = 0;
    int indx_j = 0;
    int temp = 0;

    for (indx_i = 0 ; indx_i < ( num_of_elements - 1 ); indx_i++)
    {
        for (indx_j = 0 ; indx_j < num_of_elements - indx_i - 1; indx_j++)
        {
            if (array[indx_j] > array[indx_j+1]) /* For decreasing order use < */
            {
                temp            = array[indx_j];
                array[indx_j]   = array[indx_j+1];
                array[indx_j+1] = temp;
            }
        }
    }

    return array;
}


void sendMessage(OPERATION op, char *ip_addr, char *buffer, int sockfd)
{
    char capability;
    int return_send;
    switch(op)
    {
        case JOIN:
                printf("Enter the capability of the client\n");
                //scanf("%c",&capability);
                capability = 'J';
		memset(buffer, '\0', sizeof(buffer));
                sprintf(buffer, "%c", capability);            
            break;
        case DELETE:
            
            break;
        case RESULT:
            
            break;
        default:
            printf("Invalid operation\n");
    }

    return_send= send(sockfd, buffer, strlen(buffer), 0);
    printf("Socket for send %d",sockfd);
    printf("Return send %d\n",return_send);
    printf("Oh dear, something went wrong int %d ! %s\n", errno,strerror(errno));
}

int connectToServer(char *serv_ip_addr)
{
    int sockfd = 0;
    char sendBuff[1024];
    struct sockaddr_in serv_addr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return;
    }
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 
    
    if(inet_pton(AF_INET, serv_ip_addr, &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return -1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return -1;
    }

    return sockfd;
}


void parse_input(char* rb)
{
	char *token;
    	char *buffer = NULL;
	//char s[2]=" ";
	int a=0,i=0;
    	int b[MAX_ARRAY_ELEMENTS];
	int *arr;
   /* get the first token */
   	token = strtok(rb, " ");
   /* walk through other tokens */
  	 while( token != NULL ) 
   	{
  	  printf( " %s\n", token );
	  b[a++]=atoi(token);
	  token = strtok(NULL, " ");
   	}
	printf("printing received Number\n");
	for(i=0;i<a;i++){
                printf("%d\t",b[i]);
        }
	arr = sortNumbers(b,a);
    printf("\nPrinting sorted numbers\n");
    for(i=0;i<a;i++){
            printf("%d ",arr[i]);
    }
    printf("\n");
    buffer = prepare_buffer(arr, a);
    if(NULL != buffer)
    {
       sendMessage(RESULT, ser_ip_addr, buffer,sockFd); 
    }
    else
    {
        printf("Buffer is Null, nothing to send\n");
    }
}
