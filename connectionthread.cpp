#include "connectionthread.h"
#include <QtCore>
#include <QDebug>
#include "ipccomms.h"

ConnectionThread::ConnectionThread()
{
}

void ConnectionThread::run(){
    IPC::Socket connection;
    int speed;
    int batt;
    if(connection.Connect()==0){
        connection.RequestData(3,& speed, & batt);
    }

}
