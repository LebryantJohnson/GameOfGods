// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "cppcharhelper.generated.h"


UCLASS( BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALINVENTORY_API Ucppcharhelper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Ucppcharhelper();
	// Mana vars
	UPROPERTY(BlueprintReadOnly)
	bool Manaismorethan0;
	UPROPERTY(BlueprintReadWrite)
	float Mana=100;
	UPROPERTY()
	float ManaTotal;
	UPROPERTY()
	float ManaAdded=10;
	
	// Base attribute Vars
	UPROPERTY(BlueprintReadWrite)
	int strength=1;
	UPROPERTY(BlueprintReadWrite)
	int intelligence=1;
	UPROPERTY(BlueprintReadWrite)
	int luck=1;
	UPROPERTY(BlueprintReadWrite)
	int endurance=1;
	UPROPERTY(BlueprintReadWrite)
	int agility=1;
	UPROPERTY(BlueprintReadWrite)
	int unusedlevels=1;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
	void ManaRegen();
	UFUNCTION(BlueprintCallable)
	void ManaChecker(float SpellCost);
	UFUNCTION(Client, Reliable)
	void ClientUpdateMana(float ManaToSet);
	
	FTimerHandle TimerHandle;

};


