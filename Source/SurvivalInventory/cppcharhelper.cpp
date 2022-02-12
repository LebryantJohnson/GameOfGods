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


//Mana Regen
void Ucppcharhelper::ManaRegen(){

	//check mana less than 100

	if(Mana<100)
		Mana=Mana+ManaAdded;

	//keep mana at 100 if it is 100
	else
		Mana=100;     
}

// Mana checker and calculate spell cost
void Ucppcharhelper::ManaChecker(float SpellCost)
{
	ManaTotal=Mana-SpellCost;

	if(ManaTotal>0){
		
	Mana=ManaTotal;
	Manaismorethan0=true;
		
}	
	else
	{
		Manaismorethan0=false;
		
	}
		
}