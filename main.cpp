#include "mainwindow.h"
#include <QApplication>
#include "ipccomms.h"
#include "connectionthread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ConnectionThread thread;
    thread.start();
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.showFullScreen();
    w.show();

    return a.exec();
}
