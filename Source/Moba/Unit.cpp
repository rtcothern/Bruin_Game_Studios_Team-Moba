// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "Unit.h"


// Sets default values
AUnit::AUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnit::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AUnit::AddAbility(UAbilityComponent* ability) {
	AddInstanceComponent(ability);
}

void AUnit::CastAbility(EKeyToAbilityIndex Key, TWeakObjectPtr<AActor> TargetActor, FVector2D TargetLocation)
{
	//12345: if everything wil lbe a skillshot, there's no need to reference the target actor
	//TODO: add code
	Abilities[(int)Key]->AttemptCast(TargetActor, TargetLocation);
}

