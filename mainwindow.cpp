#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_chart1 = nullptr;
    m_scatterSeries1 = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
    if(m_scatterSeries1)
        delete m_scatterSeries1;
    if(m_chart1)
        delete m_chart1;
}

void MainWindow::on_pushButton_pressed()
{


    m_scatterSeries1 = new QScatterSeries();

    int walk = 0, max= 0;
    float rand = 0.0;

    for(int i=0; i<100; i++)
    {
        rand = (float)(qrand()%10)/10;
        qDebug("%f",rand);
        if(rand > 0.5)
            walk += 1;
        else
            walk -= 1;
        if(std::abs(walk) > max)max = walk;
        m_scatterSeries1->append(i, walk);
    }

    m_chart1 = new Chart(m_scatterSeries1, "DRUNKARD", "Axis X", "Axis Y", 100, max*2, "sailor walk");
    ui->chartView->setWidget(m_chart1);
}

