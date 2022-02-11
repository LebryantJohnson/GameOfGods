// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterCharacter.h"

// Sets default values
AMasterCharacter::AMasterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    
    
}

//Mana Regem
void AMasterCharacter::ManaRegen(float ManaIn, float Delay, float ManaAdded, float& ManaOut){

//check mana less than 100

if(ManaIn<100)
ManaOut=ManaIn+ManaAdded;

//keep mana at 100 if it is 100
else
ManaOut=100;     
}

//Mana>0
void AMasterCharacter::ManaChecker(float ManaIn, float SpellCost, bool& Is0, float&ManaTotal, float& ManaOut){

ManaTotal=ManaIn-SpellCost;
ManaOut=ManaIn;

if(ManaTotal>0)
    Is0=false;
    else
    Is0=true;
}

