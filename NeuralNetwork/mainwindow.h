#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NeuralNetwork/NeuralNetwork.h"
#include "NeuralNetwork/SigmoidNeuron.h"
#include "NeuralNetwork/LearningAlgorithm.h"
#include "csvparser.hpp"
#include "csvnetworkbuilder.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    NeuralNetwork<SigmoidNeuron, 2> m_network;
    LearningAlgorithm m_algoritm{m_network};
    CSV::Data m_data;
    CSVNetworkBuilder m_builder;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
