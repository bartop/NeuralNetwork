#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "SigmoidNeuron.h"
#include "Connection.h"
#include "InputNeuron.h"
#include "ActivationFunctions.h"
#include "neuralnetwork.h"
#include "learningalgorithm.h"
#include "helper.h"
#include "weatherdatareader.h"

#include <cstdlib>

TEST_CASE("Vector arithmetics")
{
    std::vector<double> first = {1, 2, 3, 4};
    std::vector<double> second = {3, 6, 9, 12};
    std::vector<double> three = {3, 3, 3, 3};

    SECTION ("Sum")
    {
        CHECK(second == first + first + first);
        first += first + first;
        CHECK(second == first);
    }

    SECTION("Difference")
    {
        CHECK(second - first - first == first);
        second -= first + first;
        CHECK(second == first);
    }

    SECTION("Multiplication")
    {
        CHECK(second == first * three);
        first *= three;
        CHECK(second == first);
    }

    SECTION("Division")
    {
        CHECK(second/three == first);
        second /= three;
        CHECK(second == first);
    }

}


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
           c->setWeight( (rand()%100)*2/100.0 - 1.0);
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

TEST_CASE("simple NeuralNetwork test")
{
    SECTION("NeuralNetwork output size")
    {
        NeuralNetwork<SigmoidNeuron, 2> neuralNetwork({2, 1, 3});
        neuralNetwork.calculateOutput();
        CHECK(3 == neuralNetwork.getOutput().size());
    }


    SECTION( "learning XOR gate")
    {
        NeuralNetwork<SigmoidNeuron, 2> neuralNetwork({2, 10, 1});

        for (unsigned i = 0; i < 320000; ++i)
        {
            int k = i%4;
            double expected = ((k/2)^(k%2))&1;

            neuralNetwork.setInput({(double)(k/2),
                                    (double)(k%2)});
            neuralNetwork.calculateOutput();
            neuralNetwork.backPropagate({expected});
            neuralNetwork.updateWeights(0.2);

        }

        for (unsigned i = 0; i < 4; ++i)
        {
            double expected = ((i/2)^(i%2))&1;

            neuralNetwork.setInput({(double)(i/2),
                                    (double)(i%2)});

            INFO ("For inputs: " << i/2 << ", " << i%2);
            CHECK (neuralNetwork.getOutput().front() == Approx(expected).epsilon(0.01));
        }
    }
}

TEST_CASE("LearningAlgorithm test")
{
    SECTION("learning square root")
    {
        const unsigned sampleSize = 25;
        const double stepSize = 1.0;

        NeuralNetwork<SigmoidNeuron, 2> network({1, 100, 1});
        LearningAlgorithm learningAlgorithm(network);
        network.setOutputMultiplier({5.0});

        std::vector<std::vector<double>> inputs(sampleSize), outputs(sampleSize);

        double val = 0;
        for(unsigned i = 0; i < sampleSize; ++i, val += stepSize)
        {
            inputs[i].push_back(val);
            outputs[i].push_back(std::sqrt(val));
        }

        //learningAlgorithm.learn(inputs, outputs, 0.1, 100000);
        learningAlgorithm.learnUntilError(inputs, outputs, 0.5, 0.02);

        for (double input = 0.0; input < 10.0; input += 0.25)
        {
            network.setInput({input});
            CHECK(network.getOutput().front() == Approx(std::sqrt(input)).epsilon(0.1));
        }
    }
}

TEST_CASE("WeatherDataReader")
{
    WeatherDataReader reader("/home/rames/Projects/Qt/NeuralNetwork/NeuralNetwork/Data/1_avg.csv");

    SECTION("Reading data")
    {
        auto output = reader.generateTrainingData(3, 1);
        CHECK(output.first.size() == output.second.size());
        CHECK(output.first.front().size() == 3*output.second.front().size());
    }

    SECTION("Learning weather prediction")
    {
        auto data = reader.generateTrainingData(3, 1);

        NeuralNetwork<SigmoidNeuron, 2> network{data.first.front().size(), 1000, data.second.front().size()};
        LearningAlgorithm learningAlgorithm(network);

        network.setOutputMultiplier({100, 100, 360, 100, 100, 100, 100, 360, 100, 100, 100, 100, 360, 100, 100, 100, 100, 360, 100, 100, 100, 100, 360, 100, 100, 100, 100, 360, 100, 100});
        network.setOutputOffset({0, 0, 0, 100, 0, 0, 0, 0, 100, 0, 0, 0, 0, 100, 0, 0, 0, 0, 100, 0, 0, 0, 0, 100, 0, 0, 0, 0, 100, 0});

        learningAlgorithm.learn(data.first, data.second, 10);

        network.setInput(data.first[100]);

        auto networkOutput = network.getOutput();
        auto it = networkOutput.begin();

        for (auto val : data.second[100])
        {
            CHECK(*it == Approx(val).epsilon(0.1));
            ++it;
        }

    }
}

