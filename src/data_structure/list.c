#include<stdio.h>
#include<stdlib.h>

void assignGroup(CLIENT_INFO *cli)
{
	int i;
	for(i=0;i<GROUPSIZE;i++)
	{
		if (cli->capability >=1 && cli->capability <= 4)
		{
			if(strcmp(group[i].task,"ARITHMETIC")==0)
			{
				group[i].client[group[i].size]->client_addr = cli->client_addr;
				group[i].client[group[i].size]->client_port = cli->client_port;
                group[i].client[group[i].size]->in_use = false;
            	group[i].client[group[i].size]->capability = cli->capability;
          		group[i].size+=1;
			}
		}
	}
}

void storeGroupInfo(CLIENT_INFO *tmpClient)
{
    if(client == NULL)
	client  = tmpClient;

	else
    {
		tmpClient->next = client;
	    client = tmpClient;
	}
}

void print_group(){
	int i=0;
	for(i=0;i<GROUPSIZE;i++){
	    if(group[i].size == 0){
		printf("There is no element in %s group\n",group[i].name);
		continue;
	    }
	    printf("There are %d element in %s group\n",group[i].size,group[i].name);
	}
}

void defineGroup()
{
	int i;
	for(i=0;i<GROUPSIZE;i=i+3)
	{
		strcpy(group[i].task,"ARITHMETIC");
		strcpy(group[i].name,"ARITHMETIC");
		group[i].size=0;

		strcpy(group[i].task,"MAXIMUM");
                strcpy(group[i].name,"MAXIMUM");
                group[i].size=0;

		strcpy(group[i].task,"SORTING");
                strcpy(group[i].name,"SORTING");
                group[i].size=0;

	}
}

CLIENT_INFO * GetClient(void)
{
    CLIENT_INFO *new_client = NULL;
    new_client = (CLIENT_INFO *)malloc(sizeof(CLIENT_INFO));
    return new_client;
}

void AddClient(CLIENT_INFO **list, CLIENT_INFO *new_client)
{
    CLIENT_INFO *temp = NULL;
    if(NULL == *list)
    {
        *list = new_client;
        *list->next = NULL;
    }
    else
    {
        temp = *list;
        *list = new_client;
        *list->next = temp;
    }
    return;
}

void DeleteClient(CLIENT_INFO **list, struct sockaddr_in client_address)
{
    CLIENT_INFO *temp = NULL;
    CLIENT_INFO *previous = NULL;
    /* If list itself is null */
    if(NULL == *list)
    {
        printf("List is empty!!! Nothing to delete\n");
        return;
    }
    /* If list has only one client */
    if(NULL == *list->next)
    {
        if(0 == memcmp(client_address, *list->client_addr.sin_addr))
        {
            *list = NULL;
            free(*list);
        }
        else
        {
            printf("Requsted client is not there in the list\n");
        }
        return;
    }
    /* if list has more than one clients */
    temp = *list;
    while(NULL != temp->next)
    {
        previous = temp;
        if(0 == memcmp(temp->next->client_addr, client_address))
        {
            previous->next = temp->next->next;
            temp->next = NULL;
            free(temp->next);
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
}

