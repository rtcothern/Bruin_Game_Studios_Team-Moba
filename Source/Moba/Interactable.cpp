// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "Interactable.h"


// Sets default values
AInteractable::AInteractable()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AInteractable::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

bool AInteractable::IsPlayer()
{
	return false;
}

bool AInteractable::IsMinion()
{
	return false;
}

bool AInteractable::IsStructure()
{
	return false;
}

