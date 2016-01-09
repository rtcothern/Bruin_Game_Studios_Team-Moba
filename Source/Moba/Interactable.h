// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Interactable.generated.h"

UENUM()
enum class ETeam : uint8
{
	TeamA,
	TeamB,
	Neutral
};

/* Enum type which reflects the relationship between two team units. */
UENUM()
enum class ERelationship
{
	None,
	Ally,
	Enemy,
	Neutral
};


UCLASS(abstract)
class MOBA_API AInteractable : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable_Team")
	ETeam Team;

	//
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsPlayer() const;

	//
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsCreep() const;

	//
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsStructure() const;

	UFUNCTION(BlueprintCallable, Category = "")
	static ERelationship GetRelationship(const AActor * const FirstActor, const AActor * const SecondActor);
};
