#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SOCKET_PATHNAME  "/root/unixsock"
#define BUFSIZE          200

void consumer()
{
	struct sockaddr_un peer_addr;
	int len;
	int size;
	char buf[BUFSIZE];

	/* Attach to server socket */
	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0) {
		printf("consumer: error opening socket\n");
		exit(1);
	}

	printf("consumer connecting to producer\n");

	peer_addr.sun_family = AF_UNIX;
	strcpy(peer_addr.sun_path, SOCKET_PATHNAME);
	len = strlen(SOCKET_PATHNAME) + sizeof(peer_addr.sun_family);
	if (connect(sock, (struct sockaddr*)&peer_addr, len) < 0) {
		printf("consumer: error in connect\n");
		exit(1);
	}

	printf("consumer connected to producer\n");

	size = recv(sock, &buf[0], BUFSIZE, 0);
	if (size < 0) {
		printf("consumer: error in recv\n");
		exit(1);
	}

	printf("consumer received message: %s\n", &buf[0]);
}

void producer()
{
	struct sockaddr_un my_addr;
	struct sockaddr_un peer_addr;
	int status;
	int connsock;
	int len;
	socklen_t peeraddrlen;
	char *msg = "this is a message from producer to consumer";

	/* Create server socket, UNIX domain */
	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0) {
		printf("producer: error opening socket\n");
		exit(1);
	}

	/* Await connections */
	my_addr.sun_family = AF_UNIX;
	strcpy(my_addr.sun_path, SOCKET_PATHNAME);
	len = strlen(SOCKET_PATHNAME) + sizeof(my_addr.sun_family);
	unlink(SOCKET_PATHNAME);
	status = bind(sock, (struct sockaddr*)&my_addr, len);
	if (status < 0) {
		printf("producer failed to bind\n");
		exit(1);
	}
	if (listen(sock, 5) < 0) {
		printf("producer failed to listen\n");
		exit(1);
	}
	connsock = accept(sock, (struct sockaddr*)&peer_addr, &peeraddrlen);
	if (connsock < 0) {
		printf("producer failed to accept\n");
		exit(1);
	}

	/* Send out message on socket */
	status = send(connsock, &msg[0], strlen(msg)+1, 0);
	if (status < 0) {
		printf("producer failed to send\n");
		exit(1);
	}
}

int main()
{
	if (fork() == 0) {
		/* start the producer/server first */
		producer();
		exit(0);
	}
	/* parent process proceeds here */
	sleep(1);
	consumer();
	exit(0);
}
