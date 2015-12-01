#ifndef IPCCOMMS_H
#define IPCCOMMS_H

namespace IPC {
	class Socket;
public:
	Connect();
	RequestData(char type, int speed*, int batt*);

private:
	Handshake();
} 

#endif 
