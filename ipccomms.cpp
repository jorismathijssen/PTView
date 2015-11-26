#include <sys/socket.h>
#include <sys/un.h>

int init_ipc() {
	int cl,rc;
	int sock = socket(AF_LOCAL, SOCK_STREAM, 0);  // initialize domain socket
	struct sockaddr_un addr;
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, "/tmp/socket", sizeof(addr.sun_path)-1); //set socket address /tmp/socket
	if (connect(sock,addr,sizeof(addr)) < 0) //make connection
		return 1; //on error exit to state 1
	//TODO handle actual connection
}