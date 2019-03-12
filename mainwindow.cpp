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
    if(m_scatterSeries1)
        delete m_scatterSeries1;
    if(m_chart1)
        delete m_chart1;
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{

    m_scatterSeries1 = new QScatterSeries();

    int walk = 0, max= 0, XY = 0, X_2 = 0, Y_2 = 0, sum_x = 0, sum_y = 0, n = 1000, K = 10;
    double rand = 0.0, SS_xy = 0.0, SS_x = 0.0, b = 0.0, a = 0.0, last_point = 0.0;
    for(int j = 0; j < n; j += n/K )
    {
        for(int i=0; i<j; i++)
        {
            rand = (double)(qrand()%10)/10;
            qDebug("%f",rand);
            if(rand < 0.5)
                walk += 1;
            else
                walk -= 1;
            if(std::abs(walk) > max)max = walk;

        }
        m_scatterSeries1->append(j, walk);
        XY += (walk * j);
        Y_2 += (walk*walk);
        X_2 += (j*j);
        sum_x += j;
        sum_y += walk;
    }


    SS_xy = XY - (sum_x*sum_y)/n;
    SS_x = X_2 - (sum_x*sum_x)/n;

    a = SS_xy/SS_x;
    b = (sum_y - a*sum_x)/n;
    last_point = a*n + b;

    m_linear_regression = new QLineSeries();
    m_linear_regression->append(0, b);
    m_linear_regression->append(n, last_point);
    QString linear;
    if(b>=0)
        linear = QString("y = %1x+%2").arg(a).arg(b);
    else
        linear = QString("y = %1x%2").arg(a).arg(b);

    m_chart1 = new Chart(m_scatterSeries1, "DRUNKARD", "Steps", "X", n, max*2,
                         QString("%1 sailors walk").arg(K), true, m_linear_regression,
                         linear);
    ui->chartView->setWidget(m_chart1);
}

