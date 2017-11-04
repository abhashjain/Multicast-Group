#include<stdio.h>
#include<time.h>
#include<string.h>
#include "logger.h"

char* print_time()
{
    int size = 0;
    time_t t;
    char *buf;
     
    t=time(NULL); /* get current calendar time */
     
    char *timestr = asctime( localtime(&t) );
    timestr[strlen(timestr) - 1] = 0;  //Getting rid of \n
     
    size = strlen(timestr)+ 1 + 2; //Additional +2 for square braces
    buf = (char*)malloc(sizeof(char)*size);
     
    memset(buf, 0x0, size);
    snprintf(buf,size,"[%s]", timestr);
    
    return buf;
}

void debug_logger(char *str)
{
	
	FILE *fp;
	fp = fopen("../log/debug_log.txt","a+");
	fprintf(fp,"[%s]:%s : %s","DEBUG",print_time(),str);
	fclose(fp);
}

void error_logger(char *str)
{
	FILE *fp;
	fp = fopen("../log/error_log.txt","a+");
	fprintf(fp,"[%s]:%s : %s","ERROR",print_time(),str);
	fclose(fp);
}

void info_logger(char *str)
{
	FILE *fp;
	fp = fopen("../log/info_log.txt","a+");
	fprintf(fp,"[%s]:%s : %s","INFO",print_time(),str);
	fclose(fp);
}
