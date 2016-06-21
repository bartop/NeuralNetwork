#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <thread>
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

    std::unique_ptr<NeuralNetwork<SigmoidNeuron, 2>> m_network;
    std::unique_ptr<LearningAlgorithm> m_algorithm;
    CSV::Data m_data;
    CSVNetworkBuilder m_builder;
    QTimer m_timer;
    std::thread m_learningThread;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_learnButton_clicked();
    void checkProgress();
    void on_actionOpen_triggered();
    void generateData(const std::string &path);

    void on_actionSave_triggered();

    void on_actionSaveNetwork_triggered();

    void on_actionOpenNetwork_triggered();

private:
    void printCSVToTable(const CSV::Data &data, QTableWidget *table);
    void buildNetwork();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
