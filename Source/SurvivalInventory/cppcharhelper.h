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

	// Base attribute Vars
	UPROPERTY(BlueprintReadWrite)
	int strength;
	UPROPERTY(BlueprintReadWrite)
	int intelligence;
	UPROPERTY(BlueprintReadWrite)
	int luck;
	UPROPERTY(BlueprintReadWrite)
	int endurance;
	UPROPERTY(BlueprintReadWrite)
	int agility;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};


