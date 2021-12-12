// Fill out your copyright notice in the Description page of Project Settings.

#include "Network.h"
#include <cassert>
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

Network::Network()
{
}

Network::~Network()
{
}

Network::Network(const std::vector<unsigned> &topology)
{
	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; layerNum++)
	{
		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++)
		{
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Made a neuron!"));
		}

		//bias neuron
		m_layers.back().back().setOutputValue(1.0);

	}
}

void Network::feedForward(const std::vector<double>& inputValues)
{
	//error check
	assert(inputValues.size() == m_layers[0].size() - 1);

	//assign the input vals to input neurons
	for (unsigned i = 0; i < inputValues.size(); i++)
	{
		m_layers[0][i].setOutputValue(inputValues[i]);
	}

	//forwardprop
	for (unsigned layerNum = 1; layerNum < m_layers.size(); layerNum++)
	{
		Layer &prevLayer = m_layers[layerNum - 1];
		for(unsigned n = 0; n < m_layers[layerNum].size() - 1; n++)
		{
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}
}

void Network::backPropagation(const std::vector<double>& targetValues)
{
	//calculate overall net error (root mean square)
	Layer &outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1; n++)
	{
		double delta = targetValues[n] - outputLayer[n].getOutputValue();
		m_error += delta * delta;
	}
	m_error /= outputLayer.size() - 1; //Get average error squared
	m_error = sqrt(m_error); //RMS

	//calculate output layer gradients 
	for (unsigned n = 0; n < outputLayer.size() - 1; n++)
	{
		outputLayer[n].calculateOutputGradients(targetValues[n]);
	}

	//calculate gradients on hidden layers
	for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; layerNum--)
	{
		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size() - 1; n++)
		{
			hiddenLayer[n].calculateHiddenGradients(nextLayer);
		}
	}

	//For all layers from outputs to first hidden layer, update connections

	for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; layerNum--)
	{
		Layer &layer = m_layers[layerNum];
		Layer &previousLayer = m_layers[layerNum - 1];

		for (unsigned n = 0; n < layer.size() - 1; n++)
		{
			layer[n].updateInputWeights(previousLayer);
		}
	}
}

//Set Output Results in resultValues
void Network::getResult(std::vector<double>& resultValues) const
{
	resultValues.clear();

	for (unsigned n = 0; n < m_layers.back().size() - 1; n++)
	{
		resultValues.push_back(m_layers.back()[n].getOutputValue());
	}
}
