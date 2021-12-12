// Fill out your copyright notice in the Description page of Project Settings.

#include "Neuron.h"

Neuron::~Neuron()
{
}

Neuron::Neuron(unsigned numOutouts, unsigned myindex)
{
	//To tweak our learning rate
	learningRate = 0.15;
	alpha = 0.5;

	for (unsigned c = 0; c < numOutouts; c++) {
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randomWeight();
	}

	m_myIndex = myindex;
}

void Neuron::feedForward(const Layer & prevLayer)
{
	double sum = 0.0;

	for (unsigned n = 0; n < prevLayer.size(); n++)
	{
		sum += prevLayer[n].getOutputValue() * prevLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_outputValue = Neuron::transferFunction(sum);
}

void Neuron::calculateOutputGradients(double targetValue)
{
	double delta = targetValue - m_outputValue;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputValue);
}

void Neuron::calculateHiddenGradients(const Layer &nextLayer)
{
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputValue);
}

void Neuron::updateInputWeights(Layer &previousLayer)
{
	for (unsigned n = 0; n < previousLayer.size(); n++)
	{
		Neuron &neuron = previousLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

		double newDeltaWeight = 
			// training weight application learning rate
			learningRate * neuron.getOutputValue() * m_gradient + 
			//a fraction of previous delta weight
			alpha * oldDeltaWeight;

		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}

double Neuron::sumDOW(const Layer & nextLayer) const
{
	double sum = 0.0;

	for (unsigned n = 0; n < nextLayer.size() - 1; n++)
	{
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}
	return sum;
}

double Neuron::transferFunction(double x)
{
	//tanh = outputrange [-1.0..1.0]
	return tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
	return 1.0 - x*x;
}
