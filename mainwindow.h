#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"
#include <cmath>

#include <QMainWindow>
#include <QtCharts/QScatterSeries>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_pressed();

private:
    Ui::MainWindow *ui;
    Chart *m_chart1;
    QScatterSeries *m_scatterSeries1;
};

#endif // MAINWINDOW_H
