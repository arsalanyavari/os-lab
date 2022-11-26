CFLAGS= -lrt -Wall -Wextra

all: reciver sender

reciver: reciver.c
	$(CC) reciver.c -o reciver $(CFLAGS)

sender: sender.c
	$(CC) sender.c -o sender $(CFLAGS)


clean:
	rm reciver sender
