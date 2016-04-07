TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    InputNeuron.cpp \
    ActivationFunction.cpp \
    ActivationFunctions.cpp \
    SigmoidNeuron.cpp \
    helper.cpp

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
    dummy.h \
    neuralnetwork.h \
    learningalgorithm.h \
    helper.h

