TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    InputNeuron.cpp \
    ActivationFunction.cpp \
    ActivationFunctions.cpp \
    SigmoidNeuron.cpp \
    weatherdatareader.cpp

HEADERS += \
    catch.hpp \
    Connection.h \
    Node.h \
    InputNeuron.h \
    InputNode.h \
    OutputNode.h \
    ProcessingNeuron.h \
    Neuron.h \
    ActivationFunction.h \
    ActivationFunctions.h \
    SigmoidNeuron.h \
    neuralnetwork.h \
    learningalgorithm.h \
    helper.h \
    neuralnetworki.h \
    weatherdatareader.h \
    json.hpp

