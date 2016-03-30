#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "ProcessingNeuron.h"
#include "Connection.h"
#include "InputNeuron.h"
#include "ActivationFunctions.h"

TEST_CASE("basic Neuron operation")
{
    //Set up...
    ProcessingNeuron neuron(ActivationFunctions::linear);
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

TEST_CASE("Simple fixed, raw net")
{
    ProcessingNeuron neuron(ActivationFunctions::step);
    InputNeuron input[2];
    InputNeuron bias(1.0);

    Connection<Neuron> *con[3] = {neuron.createConnectionFrom(bias),
                                  neuron.createConnectionFrom(input[0]),
                                  neuron.createConnectionFrom(input[1])};

    SECTION( "NAND Gate" )
    {
        con[0]->setWeight(3.0);
        con[1]->setWeight(-2.0);
        con[2]->setWeight(-2.0);

        for (unsigned i = 0; i < 4; ++i)
        {
            input[0].setValue(i%2);
            input[1].setValue(i/2);

            neuron.invalidateOutput();
            INFO ("For inputs: " << input[0].getOutput() << ", " << input[1].getOutput());
            CHECK (neuron.getOutput() == ((~((i/2)&(i%2)))&1));
        }
    }


    for (auto &c : con)
        delete c;
}


