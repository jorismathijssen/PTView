#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QtCore>

class ConnectionThread :public QThread
{
    Q_OBJECT
public:
    explicit ConnectionThread(QObject *parent = 0 );
    void run();
    bool stop;

signals:
    void  DataRecieved(int, int);
};

#endif // CONNECTIONTHREAD_H
