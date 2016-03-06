// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "EffectComponent.h"
#include "AbilityComponent.generated.h"


class UAbilityComponent;
class AAbilityProjectile;
class UAbilityAction;
enum EventMessage;

/**
Ability Components are responsible for sending out Effect Components
(either via a projectile or direction application)
when necessary conditions are met.
These conditions include but are not limited to:
	* user input
	* ability off cooldown
	* necessary world/enviornment conditions
	* valid selected target
*/
UCLASS(Blueprintable, BlueprintType, ClassGroup = "Abilities")
class MOBA_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UAbilityAction* mRootAction;

public:
	// Sets default values for this component's properties
	UAbilityComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//Returns the Unit to which this component belongs to
	UFUNCTION(BlueprintCallable, Category = "Ability Information")
	AInteractable* GetCaster() const;

	//
	void SetRoot(UAbilityAction* rootAction);

	//
	void AttemptCast(TWeakObjectPtr<AActor> TargetActor, FVector2D TargetLocation);
};