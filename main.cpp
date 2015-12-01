#include "mainwindow.h"
#include <QApplication>
#include "ipccomms.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.showFullScreen();
    w.show();

    return a.exec();
}
