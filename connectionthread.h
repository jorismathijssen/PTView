#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QtCore>

class ConnectionThread :public QThread
{
public:
    ConnectionThread();
    void run();
};

#endif // CONNECTIONTHREAD_H
