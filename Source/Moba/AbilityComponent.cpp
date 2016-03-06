// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "AbilityProjectile.h"
#include "Interactable.h"
#include "AbilityComponent.h"
#include "AbilityAction.h"
#include "AbilityBuilder.h"

/*
	----------
	Constructors and Overloaded functions
	----------
*/
// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbilityComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UAbilityComponent::SetRoot(UAbilityAction* root) {
	mRootAction = root;
}

AInteractable * UAbilityComponent::GetCaster() const
{
	return (AInteractable*)GetOwner();
}

void UAbilityComponent::AttemptCast(TWeakObjectPtr<AActor> TargetActor, FVector2D TargetLocation) {
	//12345: return to validate
	mRootAction->Start();
}