

#include "Neuron.h"
#include "Connection.h"

int main(){
	Neuron neuron1, neuron2;
	neuron1.createConnectionTo(&neuron2);
	return 0;
}
