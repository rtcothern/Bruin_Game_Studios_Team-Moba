// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Interactable.generated.h"

//avoiding circular dependencies
class UAbilityComponent;
class UEffectComponent;

/* Enum type which represents what team an Interactable is on */
UENUM()
enum class ETeam : uint8
{
	TeamA,
	TeamB,
	Neutral
};

/* Enum type which reflects the relationship between two team units. */
UENUM(BlueprintType)
enum class ERelationship : uint8
{
	None UMETA(DisplayName = "None"),
	Ally UMETA(DisplayName = "Ally"),
	Enemy UMETA(DisplayName = "Enemy"),
	Neutral UMETA(DisplayName = "Neutral")
};

UCLASS(abstract)
class MOBA_API AInteractable : public ACharacter
{
	GENERATED_BODY()

protected:
	//All Interactables have some form of a basic interact ability ability
	//In most cases this will be a basic attack, but some cases may vary
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Basic Interaction")
	UAbilityComponent *BasicInteract;

	//The team this Interactable belongs to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable_Team")
	ETeam Team;

	//RemainingHealth = MaxHealth upon respawn
	//This value should not change often nor outside of controlled situations (e.g. leveling up)...
	//... it is therefore recommended Getter/setters be used to change its value rather than direct manipulation.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable Stats")
	int32 MaxHealth;

	//The amount of health this Interactable currently has
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Interactable Stats")
	int32 RemainingHealth;

	//Team experience gained upon the death of this Interactable
	//Assumed this will be a constant value for each type of Interactable, so editing is restricted to defautls only
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactable Stats")
	int32 ExperienceWorth;

	//Kill Streak value gained upon the death of this Interactable
	//Assumed this will be a constant value for each type of Interactable, so editing is restricted to defautls only
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactable Stats")
	int32 KillStreakWorth;

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

	//Is this interactable of type Player/MobaCharacter?
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsPlayer() const;

	//Is this Interactable of type Creep?
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsCreep() const;

	//Is this Interactable of type Structure?
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsStructure() const;

	//
	UFUNCTION(BlueprintCallable, Category = "")
	static ERelationship GetRelationship(const AActor * const FirstActor, const AActor * const SecondActor);

	UFUNCTION(BlueprintCallable, Category = "")
	void CastBasic(AActor* TargetActor);
};
