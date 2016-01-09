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

ERelationship AInteractable::GetRelationship(const AActor * const FirstActor, const AActor * const SecondActor)
{
	//preventing future accessing of nullptrs
	if (FirstActor == nullptr || SecondActor == nullptr)
	{
		UE_LOG(Units, Warning, TEXT("Interactable.cpp/GetRelationship() recieced a nullptr. FirstActor(%s), SecondActor(%s)."), FirstActor ? "valid" : "nullptr", SecondActor ? "valid" : "nullptr");
		return ERelationship::None;
	}

	//confirming passed Actors are of a type that can be on a team
	//returning 'None' if either one fails to meet that condition
	//TODO: add test for structure
	const bool bothInteractbles = FirstActor->GetClass()->IsChildOf(AInteractable::StaticClass())
		&& SecondActor->GetClass()->IsChildOf(AInteractable::StaticClass());

	if (!bothInteractbles)
	{
		return ERelationship::None;
	}

	//getting each Actor's team
	//TODO: get team if Actor is structure
	ETeam FirstTeam, SecondTeam;
	FirstTeam = ((AInteractable*)FirstActor)->Team;
	SecondTeam = ((AInteractable*)SecondActor)->Team;

	//
	if (FirstTeam == ETeam::Neutral || SecondTeam == ETeam::Neutral)
	{
		return ERelationship::Neutral;
	}
	else if (FirstTeam == SecondTeam)
	{
		return ERelationship::Ally;
	}
	
	return ERelationship::Enemy;
}
