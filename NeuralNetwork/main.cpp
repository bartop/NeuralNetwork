#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "SigmoidNeuron.h"
#include "Connection.h"
#include "InputNeuron.h"
#include "ActivationFunctions.h"


#include <cstdlib>


TEST_CASE("creation and deletion")
{
    SECTION( "InputNeuron creation and deletion")
    {
        InputNeuron *neuron = new InputNeuron();
        delete neuron;
    }

    SECTION( "SigmodNeuron creation and deletion")
    {
        SigmoidNeuron *neuron = new SigmoidNeuron();
        delete neuron;
    }

    SECTION("Connection creation and deletion")
    {
        SigmoidNeuron sigmoid;
        InputNeuron input;

        Connection<Neuron, ProcessingNeuron> *con =
                new Connection<Neuron, ProcessingNeuron>(&input, &sigmoid, 0);
        delete con;

    }
}

TEST_CASE("basic Neuron operation")
{
    //Set up...
    SigmoidNeuron neuron;
    InputNeuron input;
    Connection<Neuron, ProcessingNeuron> *con;

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

        input.setValue(1.0);
        neuron.calculateOutput();
        CHECK(neuron.getOutput() == ActivationFunctions::sigmoid(input.getOutput()));

        con->setWeight(0.0);
        neuron.calculateOutput();
        CHECK(neuron.getOutput() == ActivationFunctions::sigmoid(0));
    }

    //Tear down..
    con->getWeight();
    delete con;
}

TEST_CASE("Simple fixed, raw net")
{
    SigmoidNeuron neuron(10.0);
    InputNeuron input[2];
    InputNeuron bias(1.0);

    Connection<Neuron, ProcessingNeuron> *con[3] = {neuron.createConnectionFrom(bias),
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

            neuron.calculateOutput();
            INFO ("For inputs: " << input[0].getOutput() << ", " << input[1].getOutput());
            CHECK (std::roundf(neuron.getOutput()) == ((~((i/2)&(i%2)))&1));
        }
    }

    SECTION( "learning AND gate")
    {
        con[0]->setWeight(0.5);
        con[1]->setWeight(0.5);
        con[2]->setWeight(0.5);
        for (unsigned i = 0; i < 32000; ++i)
        {
            double expected = (((i/2)%2)&(i%2))&1;
            input[0].setValue(i%2);
            input[1].setValue((i/2)%2);

            neuron.calculateOutput();
            neuron.getOutput();

            neuron.calculateDelta(expected);
            neuron.updateWeights(0.5);
        }

        for (unsigned i = 0; i < 4; ++i)
        {
            double expected = ((i/2)&(i%2))&1;
            input[0].setValue(i%2);
            input[1].setValue(i/2);

            neuron.calculateOutput();

            INFO ("For inputs: " << input[0].getOutput() << ", " << input[1].getOutput());
            CHECK (neuron.getOutput() == Approx(expected).epsilon(0.01));
        }
    }


    for (auto &c : con)
        delete c;
}


TEST_CASE("Complex fixed, raw net")
{
    SigmoidNeuron output{10};
    SigmoidNeuron neuron[2]{10, 10};
    InputNeuron input[2];
    InputNeuron bias(1.0);

    Connection<Neuron, ProcessingNeuron> *con[] = {
                                 output.createConnectionFrom(bias),
                                 output.createConnectionFrom(neuron[0]),
                                 output.createConnectionFrom(neuron[1]),

                                 neuron[0].createConnectionFrom(bias),
                                 neuron[0].createConnectionFrom(input[0]),
                                 neuron[0].createConnectionFrom(input[1]),

                                 neuron[1].createConnectionFrom(bias),
                                 neuron[1].createConnectionFrom(input[0]),
                                 neuron[1].createConnectionFrom(input[1]),};

    SECTION( "learning XOR gate")
    {
        for (auto &c : con)
        {
          // c->setWeight( (rand()%100)*2/100.0 - 1.0);
        }

        for (unsigned i = 0; i < 3200000; ++i)
        {
            int k = i%4;
            double expected = ((k/2)^(k%2))&1;
            input[0].setValue(k%2);
            input[1].setValue(k/2);

            neuron[0].calculateOutput();
            neuron[1].calculateOutput();
            output.calculateOutput();

            output.calculateDelta(expected);
            neuron[0].calculateDelta();
            neuron[1].calculateDelta();

            neuron[0].updateWeights(0.5);
            neuron[1].updateWeights(0.5);
            output.updateWeights(0.5);

        }

        for (unsigned i = 0; i < 4; ++i)
        {
            double expected = ((i/2)^(i%2))&1;
            input[0].setValue(i%2);
            input[1].setValue(i/2);

            neuron[0].calculateOutput();
            neuron[1].calculateOutput();
            output.calculateOutput();

            INFO ("For inputs: " << input[0].getOutput() << ", " << input[1].getOutput());
            CHECK (output.getOutput() == Approx(expected).epsilon(0.01));
        }
    }


    for (auto &c : con)
        delete c;
}



