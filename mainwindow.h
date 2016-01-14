#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectionthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ConnectionThread *thread;

public:
    Ui::MainWindow *ui;
    void PlotAccuDemo();
    void PlotSnelheidDemo();

public slots:
    void aButtonClicked();
    void updateView();
    void check();
    void onDataChanged(int, int);
};


#endif // MAINWINDOW_H
