#include<stdio.h>
#include<stdbool.h>

#define MAX_NUM_OF_CLIENTS 255
#define MAX_NAME_LEN 15
#define MAX_TASK_NAME_LEN 15

char *join_group();
void leave_group();
//char *search_group();

typedef struct _client_info {
	struct in_addr client_addr;
	unsigned short client_port;
	char *grp_name;
	int capability;
    int fd;
	bool in_use;
	struct _client_info *next;	
}CLIENT_INFO;	
	
typedef struct _group_info {
	char name[MAX_NAME_LEN];
	CLIENT_INFO client[MAX_NUM_OF_CLIENTS];	
	int size;
	bool in_use;
	char task[MAX_TASK_NAME_LEN];
}GROUP_INFO;	
		
