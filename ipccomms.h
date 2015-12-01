#ifndef IPCCOMMS_H
#define IPCCOMMS_H

namespace IPC {
    class Socket {
public:
    int Connect();
    int RequestData(char type, int * speed, int * batt);

private:
    int Handshake();
    };
} 

#endif 
