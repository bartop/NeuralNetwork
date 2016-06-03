#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvparser.hpp"
#include <fstream>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_network({30, 30, 10}, SigmoidNeuron(0.9))
{
    ui->setupUi(this);
    CSV::Data csv("/home/rames/Projects/Qt/NeuralNetwork/NeuralNetwork/Data/new.csv");

    ui->tableWidget->setColumnCount(csv.getHeader().size());
    for (std::size_t i = 0; i < csv.getHeader().size(); ++i) {
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(csv.getHeader().at(i).c_str()));
    }

    ui->tableWidget->setRowCount(csv.getRows().size());

    for (std::size_t i = 0; i < csv.getRows().size(); ++i) {
        for (std::size_t j = 0; j < csv.getRows().at(i).getItems().size(); ++j) {
            std::string item = csv.getRows().at(i).getItems().at(j);
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(item.c_str()));
        }
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}
