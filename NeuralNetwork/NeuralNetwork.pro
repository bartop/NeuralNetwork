TEMPLATE = app
CONFIG += c++14
QT += core gui widgets

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    NeuralNetwork/InputNeuron.cpp \
    NeuralNetwork/SigmoidNeuron.cpp

HEADERS += \
    mainwindow.h \
    NeuralNetwork/InputNeuron.h \
    NeuralNetwork/InputNode.h \
    NeuralNetwork/Neuron.h \
    NeuralNetwork/Node.h \
    NeuralNetwork/OutputNode.h \
    NeuralNetwork/ProcessingNeuron.h \
    NeuralNetwork/SigmoidNeuron.h \
    NeuralNetwork/Connection.h \
    NeuralNetwork/helper.h \
    NeuralNetwork/json.hpp \
    NeuralNetwork/LearningAlgorithm.h \
    NeuralNetwork/NeuralNetwork.h \
    NeuralNetwork/NeuralNetworkI.h \
    NeuralNetwork/Normalizer.h \
    NeuralNetwork/loops.hpp \
    NeuralNetwork/jsonifyable.h \
    csvparser.hpp \
    csvnetworkbuilder.hpp

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
     NeuralNetwork/Range

DISTFILES += \
    deployment.pri \
    NeuralNetwork.pro.user.c125da9 \
    Data/1_avg (kopia).csv \
    Data/1_avg.csv \
    Data/2_avg (kopia).csv \
    Data/2_avg.csv \
    Data/1_avg (kopia).csv \
    Data/2_avg (kopia).csv

