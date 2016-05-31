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

UCLASS(Blueprintable, BlueprintType, Abstract)
class MOBA_API AUnit : public AInteractable
{
	GENERATED_BODY()
protected:
	//
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TArray<UAbilityComponent*> Abilities;

	//client-side function to be overloaded in blueprint so that it can call serverside respawn function
	UFUNCTION(BlueprintNativeEvent, Category = "Death")
	void RespawnCaller();

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
	//UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual void CastAbility(EKeyToAbilityIndex Key, AActor* TargetActor, FVector2D TargetLocation);
};
