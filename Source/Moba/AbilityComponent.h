// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBA_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//The maximum distance this ability can travel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
	int32 range;

	//The amout of damange this ability deals
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
	int32 damage;

	//The amount of health this ability restores
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
	int32 heal;

	//Minimum time a player must wait to cast this ability again
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
	float maxCooldown;

	//The remaining time a player must wait before being allowed to cast this ability
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Ability Stats")
	float cooldownRemaining;
};
