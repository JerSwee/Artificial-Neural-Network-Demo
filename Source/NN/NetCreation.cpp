// Fill out your copyright notice in the Description page of Project Settings.

#include "NetCreation.h"


// Sets default values
ANetCreation::ANetCreation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANetCreation::BeginPlay()
{
	Super::BeginPlay();

	//The following code needs to be altered for the tutorial to instead read in from the text file.
	//The text file contains the needed input and expected output values to be used in training.
	//*******************************************************************************************************************
	//The topology of the NN. ie: 2,2,1 layers (2 first layer, 2 second, 1 third)
	std::vector<unsigned> topology;
	topology.push_back(2);
	topology.push_back(2);
	topology.push_back(1);
	myNN = new Network(topology);

	//One round of feed forward implemented... This is not currently a fully functional NN
	//Check the Network.cpp class for more details.
	myNN->feedForward(inputValues);
	//******************************************************************************************************************

}

// Called every frame
void ANetCreation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

