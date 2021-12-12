// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "CoreMinimal.h"



struct Connection
{
	double weight;
	double deltaWeight;
};

/**
 * 
 */
class NNTUTORIAL_API Neuron
{
	typedef std::vector<Neuron> Layer;
public:
	~Neuron();
	Neuron(unsigned numOutouts, unsigned myindex);

	void setOutputValue(double val) { m_outputValue = val; };
	double getOutputValue() const { return m_outputValue; };
	void feedForward(const Layer &prevLayer);
	void calculateOutputGradients(double targetValue);
	void calculateHiddenGradients(const Layer &nextLayer);
	void updateInputWeights(Layer &previousLayer);

private:

	double learningRate; //[0.0..1.0] (0.0 slow, 0.2 medium, 1.0 fast)
	double alpha; //[0.0..n] momentum of last weight change (0.0 no change, 0.5 moderate change)

	unsigned m_myIndex;
	double m_outputValue;
	double m_gradient;
	std::vector<Connection> m_outputWeights;

	double sumDOW(const Layer &nextLayer) const;
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	static double randomWeight() { return rand() / double(RAND_MAX); };
};





