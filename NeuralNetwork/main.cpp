#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "ProcessingNeuron.h"
#include "Connection.h"
#include "InputNeuron.h"

TEST_CASE("basic Neuron operation")
{
    //Set up...
    ProcessingNeuron neuron;
    InputNeuron input;
    Connection<Neuron> *con;

    SECTION( "connection to" ) {
        con = input.createConnectionTo(&neuron);

        REQUIRE(input.getOutputs().front() == neuron.getInputs().front());
        CHECK(input.getOutputs().front()->getInput() == &input);
        CHECK(input.getOutputs().front()->getOutput() == &neuron);
    }

    SECTION( "connection from" ) {
        con = neuron.createConnectionFrom(&input);

        REQUIRE(input.getOutputs().front() == neuron.getInputs().front());
        CHECK(input.getOutputs().front()->getInput() == &input);
        CHECK(input.getOutputs().front()->getOutput() == &neuron);
    }

    SECTION( "Neurons operation" )
    {
        con = input.createConnectionTo(&neuron);
        con->setWeight(1.0);

        input.setValue(3.1415);
        REQUIRE(neuron.getOutput() == input.getOutput());

        con->setWeight(0.0);
        neuron.invalidateOutput();
        REQUIRE(neuron.getOutput() == 0);
    }

    //Tear down..
    delete con;
}
