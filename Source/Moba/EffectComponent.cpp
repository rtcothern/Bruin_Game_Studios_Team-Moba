// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "EffectComponent.h"

// Sets default values for this component's properties
UEffectComponent::UEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(true);

}

// Called when the game starts
void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEffectComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	float actualDelta;
	if (DeltaTime > Duration)
	{
		actualDelta = Duration;
		Duration = 0;
	}
	else
	{
		actualDelta = DeltaTime;
		Duration -= DeltaTime;
	}

	if (Duration >= 0)
	{
		Persist(actualDelta);
	}
	else
	{
		Cleanup();
		DestroyComponent();
	}
}

AInteractable * UEffectComponent::GetAffected() const
{
	return (AInteractable*)GetOwner();
}

AInteractable * UEffectComponent::GetCaster() const
{
	return nullptr;
}

void UEffectComponent::Apply_Implementation()
{
}

void UEffectComponent::Persist_Implementation(float delta)
{
}

void UEffectComponent::Cleanup_Implementation()
{
}