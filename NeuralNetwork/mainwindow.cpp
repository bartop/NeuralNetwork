#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvparser.hpp"
#include <QFileDialog>
#include <fstream>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    //m_data(R"(C:\Users\Rafal\Dysk Google\QtProjects\NeuralNetworkGIT\NeuralNetwork\NeuralNetwork\Data\new.csv)"),
    m_data(R"(/home/rames/Projects/Qt/NeuralNetwork/NeuralNetwork/Data/new.csv)")


{
    ui->setupUi(this);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(checkProgress()));
    printCSVToTable(m_data, ui->tableWidget);
}

MainWindow::~MainWindow()
{
    if (m_learningThread.joinable())
        m_learningThread.join();
    delete ui;
}

void MainWindow::printCSVToTable(const CSV::Data &data, QTableWidget *table)
{
    table->clear();
    table->setColumnCount(data.getHeader().size());
    for (std::size_t i = 0; i < data.getHeader().size(); ++i) {
        table->setHorizontalHeaderItem(i, new QTableWidgetItem(data.getHeader().at(i).c_str()));
    }

    table->setRowCount(data.getRows().size());

    const auto &rows = data.getRows();
    for (std::size_t i = 0; i < rows.size(); ++i) {
        const auto &items = rows[i].getItems();
        for (std::size_t j = 0; j < items.size(); ++j) {
            table->setItem(i, j, new QTableWidgetItem(((std::string)items[j]).c_str()));
        }
    }
}

void MainWindow::buildNetwork()
{
    m_network = m_builder
            .setCSVData(m_data)
            .setInertion(ui->inertionSpinBox->value())
            .setPredictedRows(ui->predictedSpinBox->value())
            .setPreviousRows(ui->previousSpinBox->value())
            .setProcessingNeuronCount(ui->neuronsCountSpinBox->value())
            .build();
}

void MainWindow::on_learnButton_clicked()
{
    if (m_learningThread.joinable())
        m_learningThread.join();
    buildNetwork();
    m_algorithm = std::unique_ptr<LearningAlgorithm>(new LearningAlgorithm(*m_network));
    m_learningThread = std::thread([this](){
        auto trainingData = m_builder.generateTrainingData();
        m_algorithm->learn(trainingData.first, trainingData.second,
                           ui->learningRateSpinBox->value(), ui->iterationsSpinBox->value());
    });
    checkProgress();
}

void MainWindow::checkProgress()
{
    auto progress = m_algorithm->getProgress();
    ui->progressBar->setValue(progress*100);
    ui->statusbar->showMessage(QString("Średni błąd średniokwadratowy: %1").arg(m_algorithm->getCurrentError()));

    if (progress < 1.f)
    {
        m_timer.setInterval(250);
        m_timer.setSingleShot(true);
        m_timer.start();
    } else
    {
        if (m_learningThread.joinable())
            m_learningThread.join();
    }

}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Wybierz plik CSV"), "", "");
    m_data = CSV::Data(fileName.toStdString());
    printCSVToTable(m_data, ui->tableWidget);
}

void MainWindow::generateData(const std::string &path)
{
    if (m_network)
    {
        CSV::Data result;
        auto testData = m_builder.setCSVData(m_data).generateTrainingData().first;

        result.setHeader(m_builder.getFilteredData().getHeader());

        for (auto row : testData)
        {
            m_network->setInput(row);

            std::vector<std::string> resultRow;
            for (double value : m_network->getOutput())
            {
                resultRow.push_back(std::to_string(value));
            }
            result.addRow(resultRow);
        }

        result.save(path);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Wybierz plik CSV"), "", "");

    generateData(fileName.toStdString());
}

void MainWindow::on_actionSaveNetwork_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Wybierz plik"), "", "JSON (*.js, *.json)");

    if (m_network && !fileName.isEmpty())
    {
        std::ofstream file(fileName.toStdString());
        file << m_network->toJson();
    }
}

void MainWindow::on_actionOpenNetwork_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Wybierz plik"), "", "JSON (*.js, *.json)");

    if (m_network && !fileName.isEmpty())
    {
        std::ifstream file(fileName.toStdString());
        nlohmann::json js;
        file >> js;
        m_network = std::unique_ptr<NeuralNetwork<>>(new NeuralNetwork<>(js));
    }
}
