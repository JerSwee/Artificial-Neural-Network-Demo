// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Neuron.h"
#include <vector>
#include "CoreMinimal.h"


/**
 * 
 */
class NN_API Network
{
	typedef std::vector<Neuron> Layer;
public:
	Network();
	~Network();

	Network(const std::vector<unsigned> &topology);

	void feedForward(const std::vector<double> &inputValues);
	void backPropagation(const std::vector<double> &targetValues);
	void getResult(std::vector<double> &resultValues) const;

private:
	double m_error;
	std::vector<Layer> m_layers;

};
