// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AbilityComponent.h"
#include "EffectComponent.h"
#include "Interactable.h"
#include "Unit.generated.h"

UENUM()
enum class EKeyToAbilityIndex
{
	Q = 0,
	W = 1,
	E = 2,
	R = 3
};

UENUM()
enum class ETeam
{
	TeamA,
	TeamB,
	Neutral
};

UCLASS(Blueprintable, BlueprintType, Abstract)
class MOBA_API AUnit : public AInteractable
{
	GENERATED_BODY()
protected:
	ETeam Team;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UEffectComponent*> AppliedEffects;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAbilityComponent*> Abilities;

	/*
	//BASIC ATTACK GOES HERE
	UPROPERTY()
	*/
public:
	// Sets default values for this character's properties
	AUnit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//
	//UFUNCTION()
	void CastAbility(EKeyToAbilityIndex Key, TWeakObjectPtr<AActor> TargetActor, FVector2D TargetLocation);

	//
	UFUNCTION(BlueprintCallable, Category = "")
	ETeam GetTeam() const;

	//
	UFUNCTION(BlueprintCallable, Category = "")
	static ERelationship GetRelationship(const AActor * const FirstActor, const AActor * const SecondActor);
};
