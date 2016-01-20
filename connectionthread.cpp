#include "connectionthread.h"
#include <QtCore>
#include <QDebug>
#include "ipccomms.h"
#include <unistd.h>


IPC::Socket connection;

ConnectionThread::ConnectionThread(QObject *parent)  :
    QThread(parent)
{

}

void ConnectionThread::run() {
    int speed = 0;
    int batt = 0;
    int value = connection.Connect();
    if(value == 0){
        qDebug("Connection succes");
        while(true){
            connection.RequestData(3,&batt,&speed);
            emit DataRecieved(speed, batt);
            this->msleep(1000);
        }
    }
    else {
        qDebug("Connection failed");
    }
}


