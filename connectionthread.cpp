#include "connectionthread.h"
#include <QtCore>
#include <QDebug>
#include "ipccomms.h"

ConnectionThread::ConnectionThread(QObject *parent)  :
    QThread(parent)
{

}

void ConnectionThread::run(){
    IPC::Socket connection;
    int speed = 137;
    int batt = 69;
    qDebug("BEFORE CONNECTION");
    int value = connection.Connect();
    if(value == 0){
        qDebug("Connection succes");
        while(true){
            connection.RequestData(3,&batt,&speed);
            emit DataRecieved(speed, batt);
            this->msleep(800);
        }
    }else{
        qDebug("Connection failed");
        qDebug() << value;
    }
}


