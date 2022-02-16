// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterCharacter.h"

// Sets default values
AMasterCharacter::AMasterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates=true;
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

void AMasterCharacter::Multic_MeleeMontages_Implementation(UAnimMontage* anim, UAnimMontage* anim1, UAnimMontage* anim2,
	UAnimMontage* anim3, UAnimMontage* anim4)
{
	PlayAnimMontage(anim,1);
	AttackCount=AttackCount++;
}

void AMasterCharacter::Server_StabMontage_Implementation(UAnimMontage* anim, UAnimMontage* anim1, UAnimMontage* anim2,
														UAnimMontage* anim3, UAnimMontage* anim4)
{
	Multic_MeleeMontages(anim,anim1,anim2,anim3,anim4);
}

void AMasterCharacter::Server_GetMeleeMontages_Implementation(UAnimMontage* anim, UAnimMontage* anim1,
                                                              UAnimMontage* anim2, UAnimMontage* anim3, UAnimMontage* anim4, bool itemisheld)
{
	if (itemisheld)
	{
		Server_StabMontage(anim,anim1,anim2,anim3,anim4);
		
	}
}



void AMasterCharacter::Server_SpawnSpell_Implementation(UClass* ClassIn, FVector SpawnTransform, AActor* OwnerIn, APawn* pawnIn, FRotator RotIn)
{
	const FVector Location=SpawnTransform;
	UClass* ClassToSpawn=ClassIn;
	const FRotator rotation=RotIn;

	FActorSpawnParameters Params;
	Params.Owner = OwnerIn;
	Params.Instigator = pawnIn;
	
	GetWorld()->SpawnActor<AActor>(ClassToSpawn, Location, rotation, Params);
	
	
}




