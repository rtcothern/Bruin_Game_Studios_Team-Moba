// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.h"
#include "Structure.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API AStructure : public AInteractable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AStructure();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Structure Stats")
		float InteractionRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Structure Stats")
		float Test;
};
