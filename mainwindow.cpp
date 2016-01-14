#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ipccomms.h"
#include "connectionthread.h"
#include <unistd.h>

bool locked = true;
QTimer *timer1;
QTimer *timer2;

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TabManager->setTabEnabled(1,false);
    ui->TabManager->setTabEnabled(2,false);
    ui->label_2->hide();
    ui->label_3->hide();
    ui->progressBar->hide();
    ui->lcdNumber_2->hide();
    connect(ui->Unlock,SIGNAL(pressed()),this,SLOT(aButtonClicked()));
    timer1 = new QTimer(this);
     connect(timer1, SIGNAL(timeout()), this, SLOT(check()));
     timer2 = new QTimer(this);
     connect(timer2, SIGNAL(timeout()), this, SLOT(updateView()));

    this->setStyleSheet("QTabBar::tab { height: 85px; width: 50px; }");
    ui->lcdNumber_2->setNumDigits(4);
    PlotSnelheidDemo();
    PlotAccuDemo();
}

void MainWindow::aButtonClicked() {
     timer1->start(1000);
}

void MainWindow::check(){
    timer1->stop();
    if(ui->Unlock->isDown()){
        ui->label_4->setText("1 sec");
         timer2->start(1000);
    }
}

void MainWindow::updateView(){
     if(ui->Unlock->isDown()){
    ui->Unlock->hide();
    ui->label->hide();
    ui->label_4->hide();
    ui->TabManager->setTabEnabled(1,true);
    ui->TabManager->setTabEnabled(2,true);
    ui->label_2->show();
    ui->label_3->show();
    ui->progressBar->show();
    ui->lcdNumber_2->show();
    char output[101];
    output[100] = 0;
    FILE *in;
    in = popen("./prog", "r");
    while(fgets(output, 100, in) != NULL) {
        qDebug() << QString(output);
    }
    usleep(5000);
    thread = new ConnectionThread(this);
    qDebug("Voor connect");
    connect(thread, SIGNAL(DataRecieved(int,int)), this, SLOT(onDataChanged(int,int)));
    thread->start();
    qDebug("Na connect");
     }
     else{
         ui->label_4->setText("2 sec");
        timer2->stop();
     }
}

void MainWindow::onDataChanged(int speed, int batt){
    ui->lcdNumber_2->display(speed);
    ui->progressBar->setValue(batt);
}

void MainWindow::PlotAccuDemo()
{
    //For plotting accu graph
    QVector<double> x(100), y(500);
    for (int i=0; i<10; ++i)
    {
      x[i] = 0+i; //Lets fill the data
      y[i] = 100-i;
    }
    ui->graph->addGraph();
    ui->graph->graph(0)->setData(x, y);
    ui->graph->xAxis->setLabel("Tijd (min)");
    ui->graph->yAxis->setLabel("Percentage (%)");
    ui->graph->xAxis->setRange(0, 10);
    ui->graph->yAxis->setRange(0, 100);
    ui->graph->yAxis->setAutoTickCount(9);
    ui->graph->xAxis->setAutoTickCount(9);
    ui->graph->replot();
}

void MainWindow::PlotSnelheidDemo()
{
    QVector<double> x(100), y(500);
    for (int i=0; i<60; ++i)
    {
      x[i] = 0+i;
      qsrand(time(NULL));
      y[i] = 0 + qrand() % 9;
    }
    ui->graph_2->addGraph();
    ui->graph_2->graph(0)->setData(x, y);
    ui->graph_2->xAxis->setLabel("Tijd (min)");
    ui->graph_2->yAxis->setLabel("Snelheid (m/s)");
    ui->graph_2->xAxis->setRange(0, 10);
    ui->graph_2->yAxis->setRange(0, 10);
    ui->graph_2->yAxis->setAutoTickCount(9);
    ui->graph_2->xAxis->setAutoTickCount(9);
    ui->graph_2->replot();
}


MainWindow::~MainWindow()
{
    delete ui;
}
