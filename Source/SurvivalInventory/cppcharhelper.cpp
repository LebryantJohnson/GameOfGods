// Fill out your copyright notice in the Description page of Project Settings.


#include "cppcharhelper.h"

// Sets default values for this component's properties
Ucppcharhelper::Ucppcharhelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Ucppcharhelper::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void Ucppcharhelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Mana Checker
void Ucppcharhelper::ManaRegen(float ManaIn, float Delay, float ManaAdded, float& ManaOut){

//check mana less than 100

if(ManaIn<100)
ManaOut=ManaIn+ManaAdded;

//keep mana at 100 if it is 100
else
ManaOut=100;      
}    

