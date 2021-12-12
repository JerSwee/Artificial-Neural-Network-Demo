// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Network.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetCreation.generated.h"

UCLASS()
class NNTUTORIAL_API ANetCreation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetCreation();
	Network* myNN;
	std::vector<double> inputValues;
	std::vector<double> targetValues;
	std::vector<double> resultValues;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
};
