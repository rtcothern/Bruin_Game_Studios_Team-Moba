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

ETeam AUnit::GetTeam() const
{
	return Team;
}

void AUnit::CastAbility(EKeyToAbilityIndex Key, TWeakObjectPtr<AActor> TargetActor, FVector2D TargetLocation)
{
	Abilities[(int32)Key]->SetTarget(TargetActor, TargetLocation);
	Abilities[(int32)Key]->AttemptCast();
}

ERelationship AUnit::GetRelationship(const AActor * const FirstActor, const AActor * const SecondActor)
{
	//preventing future accessing of nullptrs
	if (FirstActor == nullptr || SecondActor == nullptr)
	{
		UE_LOG(Units, Warning, TEXT("Unit.cpp/GetRelationship() recieced a nullptr. FirstActor(%s), SecondActor(%s)."), FirstActor ? "valid" : "nullptr", SecondActor ? "valid" : "nullptr");
		return ERelationship::None;
	}

	//WARNING! Code beyond this log message will need to be updated later
	UE_LOG(Units, Warning, TEXT("Unit.cpp/GetRelationship() only tests Unit/Unit relationships. Structure/* will always return 'None'."));

	//confirming passed Actors are of a type that can be on a team
	//returning 'None' if either one fails to meet that condition
	//TODO: add test for structure
	const bool
		bFirstUnit = FirstActor->GetClass() == AUnit::StaticClass(),
		bFirstStructure = false,
		bSecondUnit = SecondActor->GetClass() == AUnit::StaticClass(),
		bSecondStructure = false;

	if(!(
		(bFirstUnit || bFirstStructure) &&
		(bSecondUnit || bSecondStructure)
		))
	{
		return ERelationship::None;
	}

	//getting each Actor's team
	//TODO: get team if Actor is structure
	ETeam FirstTeam, SecondTeam;
	if (bFirstUnit)
	{
		FirstTeam = ((AUnit*)FirstActor)->GetTeam();
	}
	else if (bFirstStructure)
	{
	}

	if (bSecondUnit)
	{
		SecondTeam = ((AUnit*)SecondActor)->GetTeam();
	}
	else if (bSecondStructure)
	{
	}

	//
	if (FirstTeam == ETeam::Neutral || SecondTeam == ETeam::Neutral)
	{
		return ERelationship::Neutral;
	}
	else if (FirstTeam == SecondTeam)
	{
		return ERelationship::Ally;
	}
	else
	{
		return ERelationship::Enemy;
	}
}