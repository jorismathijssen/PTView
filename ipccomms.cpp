#include <sys/socket.h>
#include <sys/un.h>
#include "ipccomms.h"
#include "ipcproto.h"
#include <unistd.h>
#include <error.h>
int sock;
namespace IPC {

    int Socket::Connect() {
        int cl,rc;
        sock = socket(AF_LOCAL, SOCK_STREAM, 0);
        // initialize domain socket
        struct sockaddr_un addr;
        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, "/tmp/socket", sizeof(addr.sun_path)-1);
        //set socket address /tmp/socket
        if (connect(sock,(struct sockaddr *) &addr,sizeof(addr)) < 0)  return 2;
        //on error exit to state 1
        if (Handshake()) return 3;
        //Handshake failed (connection is probably dead)
        return 0;
        //TODO handle actual connection
    }

    int Socket::Handshake() {
        char buffer;
        int n;
        buffer = PT_HANDSHAKE;
        n = write(sock,&buffer,sizeof(char));
        if (n < 0) return 1;
        n = read(sock,&buffer,1);
        if (n < 0)  return 1;
        if(buffer!=PT_ACK) return 1;
        return 0;
    }

    int Socket::RequestData(char type, int * speed, int * batt)
    {
        char buffer;
        char largebuffer[255];
        int n;
        buffer = PT_REQUEST_ALL;
        n = write(sock,&buffer,sizeof(char));
        //TODO actually implement different requests
        if (n < 0) return 1;
        n = read(sock,&buffer,sizeof(char));
        if (n < 0) return 1;
        if(buffer!=PT_RESPONSE) return 1;
        //incorrect response, fail
        //TODO handle incoming data
        n = read(sock,largebuffer,8);
        if (n < 0) return 1;
        //HANDLE DATA
        memcpy(batt, largebuffer, 4);
        memcpy(speed, largebuffer+4, 4);
        return 0;
    }
}
