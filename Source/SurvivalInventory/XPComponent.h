// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XPComponent.generated.h"


UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALINVENTORY_API UXPComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UXPComponent();

	UPROPERTY(BlueprintReadWrite)
	int currentlevel=1;

	UPROPERTY(BlueprintReadWrite)
	int levelcap=20;

	UPROPERTY(BlueprintReadWrite)
	float currentxp;

	UPROPERTY(BlueprintReadWrite)
	float currentmaxXP=500;

	UPROPERTY(BlueprintReadWrite)
	float bufferxp;

	UPROPERTY(BlueprintReadWrite)
	float currentpercentage;

	UPROPERTY()
	float RemainingXP;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void CalculatePercentage();

	UFUNCTION(BlueprintCallable)
	void CalculateMaxXp();

	UFUNCTION(BlueprintCallable)
	void AddXP(float AddedXP);

	UFUNCTION(BlueprintCallable)
	void LevelUp();
};
