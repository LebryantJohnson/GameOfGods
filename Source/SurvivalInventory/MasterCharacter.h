// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "MasterCharacter.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SURVIVALINVENTORY_API AMasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMasterCharacter();


	UPROPERTY(BlueprintReadWrite)
	int AttackCount;	
private:
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Server, Unreliable)
	void Server_SpawnSpell(UClass* ClassIn, FVector SpawnTransform, AActor* OwnerIn, APawn* pawnIn, FRotator RotIn);

	UFUNCTION(NetMulticast,Unreliable)
	void Multic_MeleeMontages(UAnimMontage* anim,UAnimMontage* anim1,UAnimMontage* anim2,UAnimMontage* anim3,UAnimMontage* anim4);
	
	UFUNCTION(Server, Unreliable,BlueprintCallable)
	void Server_StabMontage(UAnimMontage* anim,UAnimMontage* anim1,UAnimMontage* anim2,UAnimMontage* anim3,UAnimMontage* anim4);

	UFUNCTION(Server, Unreliable,BlueprintCallable)
	void Server_GetMeleeMontages(UAnimMontage* anim,UAnimMontage* anim1,UAnimMontage* anim2,UAnimMontage* anim3,UAnimMontage* anim4, bool itemisheld);

	
};