#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvparser.hpp"
#include <fstream>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_network({30, 30, 10}, SigmoidNeuron(0.9)),
    m_data(R"(C:\Users\Rafal\Dysk Google\QtProjects\NeuralNetworkGIT\NeuralNetwork\NeuralNetwork\Data\new.csv)")

{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(m_data.getHeader().size());
    for (std::size_t i = 0; i < m_data.getHeader().size(); ++i) {
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(m_data.getHeader().at(i).c_str()));
    }

    ui->tableWidget->setRowCount(m_data.getRows().size());

    for (std::size_t i = 0; i < m_data.getRows().size(); ++i) {
        for (std::size_t j = 0; j < m_data.getRows().at(i).getItems().size(); ++j) {
            std::string item = m_data.getRows().at(i).getItems().at(j);
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(item.c_str()));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
