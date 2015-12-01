#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ipccomms.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    IPC::Socket connection;
    ui->setupUi(this);
    this->setStyleSheet("QTabBar::tab { height: 85px; width: 50px; }");
    ui->lcdNumber_2->setNumDigits(3);
    int speed;
    int batt;
    if(connection.Connect()==0){
        connection.RequestData(3,& speed, & batt);
        ui->textBrowser->setText(QString::number(speed) + " EN " + QString::number(batt));
        ui->lcdNumber_2->display(speed);
        ui->progressBar->setValue(batt);
    }
    else{
        ui->textBrowser->setText("GODVER NIET CONNECTED" + QString::number(connection.Connect()));
    }
    PlotSnelheidDemo();
    PlotAccuDemo();
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
    ui->progressBar->setValue(40);
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
