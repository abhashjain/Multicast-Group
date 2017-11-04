CC = gcc
CFLAGS = -I -g -Wall
CFLAGS += -DLOG_ERROR_DBG
CFLAGS += -DLOG_INFO_DBG
CFLAGS += -DLOG_ENTRY_DBG
CFLAGS += -DLOG_EXIT_DBG

INCLUDE_PATH = ../includes

default:	client
client:	client.o
		$(CC) $(CFLAGS) -o client client.o

client.o:	client.c $(INCLUDE_PATH)/apidata.h $(INCLUDE_PATH)/logger.h
			$(CC) $(CFLAGS) -c client.c

clean:
		$(RM) *.o *~