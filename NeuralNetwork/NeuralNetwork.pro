TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    InputNeuron.cpp \
    ProcessingNeuron.cpp \
    ActivationFunction.cpp \
    ActivationFunctions.cpp

include(deployment.pri)
qtcAddDeployment()

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
    ActivationFunctions.h

