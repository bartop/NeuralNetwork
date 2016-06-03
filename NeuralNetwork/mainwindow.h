#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NeuralNetwork/NeuralNetwork.h"
#include "NeuralNetwork/SigmoidNeuron.h"
#include "NeuralNetwork/LearningAlgorithm.h"
#include "weatherdatareader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    NeuralNetwork<SigmoidNeuron, 2> m_network;
    LearningAlgorithm m_algoritm{m_network};
    WeatherDataReader m_dataReader{"/home/rames/Projects/Qt/NeuralNetwork/NeuralNetwork/Data/1_avg.csv"};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
