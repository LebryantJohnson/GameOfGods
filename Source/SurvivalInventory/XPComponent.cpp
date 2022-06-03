// Fill out your copyright notice in the Description page of Project Settings.


#include "XPComponent.h"

// Sets default values for this component's properties
UXPComponent::UXPComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UXPComponent::BeginPlay()
{
	Super::BeginPlay();
	CalculatePercentage();
	
	// ...
	
}


// Called every frame
void UXPComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// ...
}

void UXPComponent::CalculatePercentage()
{
	currentpercentage=currentxp/currentmaxXP;
}

void UXPComponent::CalculateMaxXp()
{
	currentmaxXP=currentmaxXP*1.7;
	currentmaxXP=ceil(currentmaxXP);
}

void UXPComponent::AddXP(float AddedXP)
{
	bufferxp=AddedXP+bufferxp;
}

void UXPComponent::LevelUp()
{
	if (currentlevel>levelcap)
	{
		currentxp=currentmaxXP;
		bufferxp=currentmaxXP;
	}
	else
	{
		currentlevel++;
		UnSpentLevels++;
		RemainingXP=bufferxp=currentmaxXP;
		CalculateMaxXp();
		currentxp=0;
		bufferxp=0;
		AddXP(RemainingXP);
						
	}
		
}


