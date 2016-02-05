// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "Interactable.h"
#include "EffectComponent.h"
#include "AbilityComponent.h"


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

bool AInteractable::ApplyEffect(UClass* EffectClassType)
{
	//Checking to make sure the passed class is of a type we expect (namely, it is a subclass EffectComponent)
	if (!EffectClassType->IsChildOf(UEffectComponent::StaticClass()))
	{
		UE_LOG(Interactables, Warning, TEXT("Interactable/ApplyEffect(): Passed Class is not a subclass of EffectComponent"));
		return false;
	}

	UEffectComponent *Effect = (UEffectComponent*)NewObject<UEffectComponent>(this, EffectClassType);
	Effect->RegisterComponent();
	Effect->Apply();

	return true;
}

float AInteractable::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	RemainingHealth -= DamageAmount;

	if (RemainingHealth <= 0)
	{

	}

	return RemainingHealth;
}

ERelationship AInteractable::GetRelationship(const AActor * const FirstActor, const AActor * const SecondActor)
{
	//preventing future accessing of nullptrs
	if (FirstActor == nullptr || SecondActor == nullptr)
	{
		UE_LOG(Interactables, Warning, TEXT("Interactable.cpp/GetRelationship() recieced a nullptr. FirstActor(%s), SecondActor(%s)."), FirstActor ? "valid" : "nullptr", SecondActor ? "valid" : "nullptr");
		return ERelationship::None;
	}

	//confirming passed Actors are of a type that can be on a team
	//returning 'None' if either one fails to meet that condition
	const bool bothInteractbles = FirstActor->GetClass()->IsChildOf(AInteractable::StaticClass())
		&& SecondActor->GetClass()->IsChildOf(AInteractable::StaticClass());

	if (!bothInteractbles)
	{
		return ERelationship::None;
	}

	//getting each Actor's team
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
	else
	{
		return ERelationship::Enemy;
	}
}

void AInteractable::CastBasic(AActor* TargetActor) {
	BasicInteract->SetTarget(TargetActor, FVector2D::ZeroVector);
	BasicInteract->AttemptCast();
}

bool AInteractable::IsPlayer() const
{
	return false;
}

bool AInteractable::IsCreep() const
{
	return false;
}

bool AInteractable::IsStructure() const
{
	return false;
}