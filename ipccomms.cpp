#include <sys/socket.h>
#include <sys/un.h>
#include "ipccomms.h"
#include "ipcproto.h"

int sock;

int Socket::Connect() {
	int cl,rc;
	sock = socket(AF_LOCAL, SOCK_STREAM, 0);  // initialize domain socket
	struct sockaddr_un addr;
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, "/tmp/socket", sizeof(addr.sun_path)-1); //set socket address /tmp/socket
	if (connect(sock,addr,sizeof(addr)) < 0) //make connection
		return 1; //on error exit to state 1
	if (Handshake())
		return 1; //Handshake failed (connection is probably dead)
	return 0;
	//TODO handle actual connection
}

int Socket::Handshake() {
	char buffer;
	n = write(sock,PT_HANDSHAKE,sizeof(char));
	if (n < 0) 
		error("ERROR writing to socket");
	n = read(sock,buffer,sizeof(char));
	if (n < 0) 
		error("ERROR reading from socket");
	if(buffer!=PT_ACK)
		return 1;
	return 0
}

int Socket::RequestData(char type=3, int speed*, int batt*) { //can request different types 
	char buffer;
	char largebuffer[255];
	n = write(sock,PT_REQUEST_ALL,sizeof(char));//TODO actually implement different requests
	if (n < 0) 
		error("ERROR writing to socket");
	n = read(sock,buffer,sizeof(char));
	if (n < 0) 
		error("ERROR reading from socket");
	if(buffer!=PT_RESPONSE) 
		return 1;//incorrect response, fail
	//TODO handle incoming data
	n = read(sock,largebuffer,8);
	if (n < 0) 
		error("ERROR reading from socket");
	//HANDLE DATA
	memcpy(batt, &buffer, 4);
	memcpy(speed, &buffer+4, 4);
	return 0
}