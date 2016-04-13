// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "EffectComponent.h"
#include "AbilityComponent.generated.h"



//present to remove circular dependencies
class Unit;

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
	protected:
		//Called during object construction
		//Default implementation treats ability like self-cast ability
		UFUNCTION(BlueprintNativeEvent)
		void Initialize();

		//RemainingCooldown -= DeltaTime
		void UpdateRemainingCooldown(float DeltaTime);

		//RemainingCooldown = MaxCooldown
		void ResetCooldown();

		//CooldownRemaining > 0?
		bool IsOnCooldown() const;

		//Checks if TargetActor is valid. If not, checks to see if TargetLocation is valid.
		//If a TargetActor is found to be valid, updates TargetLocation to that of the actor.
		bool IsTargetValid();

		//Compares distance from (X,Y) position of Caster to (X,Y) position of TargetLocation against MaxRange
		bool IsTargetInRange() const;

		//Blueprint implementable function which allows extra conditions to be tested before allowing Cast() to be called
		//If not implemented, it is assumed that no additional conditions need to be met,
		//so default implementation returns true
		UFUNCTION(BlueprintNativeEvent)
		bool AreExtraConditionsMet();

		//Tests if all conditions (off cooldown, valid target, target in range, additional conditions) have been met
		//If it evaluates to true, Cast() is called.
		bool CanBeCast();

		//Called when all sufficient ability conditions are met.
		//Implement this function to apply immediate, targeted effects
		UFUNCTION(BlueprintNativeEvent)
		void CastAbility();

		//Spawns AbilityProjectile if ability has projectile
		void CastProjectile();

		//Ability name
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Stats")
		FName Name;

		//The maximum distance this ability can travel
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Stats")
		int32 MaxRange;

		//Does this Ability spawn a projectile upon cast?
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
		bool bHasProjectile;
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
		float projectileSize;
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
		bool bProjectilePierces;

		//The type of AbilityProjectile to be spawned upon successful cast
		UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		UClass *AbilityProjectileClass;

		//The location relative to the Caster's position where the projectile will spawn
		UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		FVector ProjectileRelativeSpawnLocation;

		//The value CooldownRemaining is set to after this Ability successfully casts
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown")
		float MaxCooldown;

		//Time remaining until this Ability can be cast again
		UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Cooldown")
		float RemainingCooldown;

		/* NOTE: a 'potential valid target' is something targeted which has yet to be checked for validity */
		//Does this Ability require a target in order to be cast?
		//If false, all variables concerned with target validity are irrelevant.
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Target Validity Requirements")
		bool bTargetedAbility;

		//Are Players potential valid targets for this Ability?
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Target Validity Requirements")
		bool bPlayerValidTarget;

		//Are Creeps potential valid targets for this Ability?
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Target Validity Requirements")
		bool bCreepValidTarget;

		//Are Structures potential valid targets for this Ability?
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Target Validity Requirements")
		bool bStructureValidTarget;

		//Is a Location not occupied by a Player, Creep, or Structure a potential valid target for this Ability?
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Target Validity Requirements")
		bool bLocationValidTarget;

		//Are Allies potential valid targets for this Ability?
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Target Validity Requirements")
		bool bAllyValidTarget;

		//Are Enemies potential valid targets for this Ability?
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Target Validity Requirements")
		bool bEnemyValidTarget;

		//Is anything Neutral a potential valid target for this Ability?
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Target Validity Requirements")
		bool bNeutralValidTarget;

		//The Actor this Ability targeted during its last attempted cast
		UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Target Selected")
		TWeakObjectPtr<AActor> TargetActor;
		
		//The world location this Ability targeted during its last attempted cast
		UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Target Selected")
		FVector2D TargetLocation;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EVO")
			TArray<class UEvo*> evos;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EVO")
			class UEvo* activeEvo;
		UFUNCTION(BlueprintCallable, Category = "EVO")
			void skillUp(uint8 newRank);
	public:	
		UFUNCTION(BlueprintCallable, Category = "Ability Information")
			void onAbilityEnd();

		//Value to be assigned to MaxRange variable if ability only affects caster
		const static int32 RANGE_SELF;

		//Value to be assigned to MaxRange variable if ability has global range
		const static int32 RANGE_GLOBAL;

		// Sets default values for this component's properties
		UAbilityComponent();

		// Called when the game starts
		virtual void BeginPlay() override;
	
		// Called every frame
		virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		//Will only cast ability/projectile if CanBeCast() returns true
		void AttemptCast();

		//Returns the Unit to which this component belongs to
		UFUNCTION(BlueprintCallable, Category = "Ability Information")
		AInteractable* GetCaster() const;

		//Sets all target related class variables
		//All boolean defaults will assume the calling Ability is not a targeted ability
		UFUNCTION(BlueprintCallable, Category = "Target Validity Requirements")
		void SetTargetParameters(bool bTargeted = false, bool bPlayer = false, bool bCreep = false, bool bStructure = false, bool bLocation = false, bool bAlly = false, bool bEnemy = false, bool bNeutral = false);

		//
		void SetTarget(TWeakObjectPtr<AActor> DirectTarget, FVector2D Location);

		void SetProjectileSize(float f) { projectileSize = f; };
		float GetProjectileSize() { return projectileSize; };

		void SetProjectilePierces(bool b) { bProjectilePierces = b; };
};
