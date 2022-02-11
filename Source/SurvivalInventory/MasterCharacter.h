// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MasterCharacter.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SURVIVALINVENTORY_API AMasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMasterCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    UFUNCTION(BlueprintCallable)
        void ManaRegen(float ManaIn, float Delay, float ManaAdded, float& ManaOut);
    UFUNCTION(BlueprintPure)
        void ManaChecker(float ManaIn, float SpellCost,bool& Is0, float& ManaTotal, float& ManaOut);



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
