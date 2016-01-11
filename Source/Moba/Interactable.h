// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Interactable.generated.h"

//avoiding circular dependencies
class UEffectComponent;

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
private:
	//Array of EffectCompoents currently attached to this Interactable
	//VisibleInstanceOnly because 
	UPROPERTY(VisibleInstanceOnly)
	TArray<UEffectComponent*> AppliedEffects;

public:
	

	// Sets default values for this character's properties
	AInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Attaches passed effect to itself and then calls Effect's OnApply() function
	//Returns false if passed Class is not a subclass of EffectComponent
	UFUNCTION(BlueprintCallable, Category = "Abilities and Effects")
	bool ApplyEffect(UClass* EffectClassType);

	//Removes the passed Effect from AppliedEffects
	UFUNCTION(BlueprintCallable, Category = "Abilities and Effects")
	void RemoveEffect(UEffectComponent *Effect);

	//
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsPlayer() const;

	//
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsCreep() const;

	//
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsStructure() const;

	//
	UFUNCTION(BlueprintCallable, Category = "")
	static ERelationship GetRelationship(const AActor * const FirstActor, const AActor * const SecondActor);

	//The team the Interactable is on
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable_Team")
	ETeam Team;
};
