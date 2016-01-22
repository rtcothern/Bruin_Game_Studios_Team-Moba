// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "EffectComponent.h"


void UEffectComponent::Persist_Implementation()
{
}

// Sets default values for this component's properties
UEffectComponent::UEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(true);

	Initialize();
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

	Duration -= DeltaTime;

	if (Duration >= 0)
	{
		Persist();
	}
	else
	{
		DestroyComponent();
	}
}

void UEffectComponent::Initialize_Implementation()
{
}

void UEffectComponent::OnApply_Implementation()
{
}