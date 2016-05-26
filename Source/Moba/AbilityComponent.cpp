// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "AbilityProjectile.h"
#include "Interactable.h"
#include "Evo.h"
#include "AbilityComponent.h"
#include "MobaCharacter.h"

const int32
	UAbilityComponent::RANGE_SELF = 0,
	UAbilityComponent::RANGE_GLOBAL = -1;



/*
	----------
	Constructors and Overloaded functions
	----------
*/
// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	activeEvo = nullptr;
	evos.Init(nullptr, 3);

	Initialize();
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbilityComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	UpdateRemainingCooldown(DeltaTime);
}

void UAbilityComponent::Initialize_Implementation()
{
	Name = TEXT("");
	MaxRange = RANGE_SELF;
	bHasProjectile = false;
	AbilityProjectileClass = nullptr;
	MaxCooldown = 0;
	RemainingCooldown = 0;
	SetTargetParameters();
}

bool UAbilityComponent::AreExtraConditionsMet_Implementation()
{
	return true;
}

/*
	----------
	Cooldown related functions
	----------
*/
bool UAbilityComponent::IsOnCooldown() const
{
	return RemainingCooldown > 0;
}

void UAbilityComponent::UpdateRemainingCooldown(float DeltaTime)
{
	if((RemainingCooldown -= DeltaTime) < 0)
	{
		RemainingCooldown = 0;
	}
}

void UAbilityComponent::ResetCooldown()
{
	RemainingCooldown = MaxCooldown;
}

/*
	----------
	Casting Related Functions
	----------
*/

bool UAbilityComponent::AttemptCast()
{
	if(!CanBeCast())
	{
		return false;
	}	

		CastAbility();

	if (bHasProjectile)
	{
		CastProjectile();
	}

	ResetCooldown();
	return true;
}

bool UAbilityComponent::CanBeCast()
{
	//true if the ability was cast by a player character
	bool isCharacter = this->GetCaster()->IsPlayer();

	if (IsOnCooldown() || !IsTargetValid() || !IsTargetInRange() || !AreExtraConditionsMet())
	{
		if (isCharacter && IsOnCooldown()) //sends message to log if ability is on cooldown
		{                                  //checking cooldown takes priorty over checking if the player has enough mana
			UE_LOG(LogTemp, Warning, TEXT("Ability on cooldown!"));
		}
		return false;
	}

	//If the ability was cast by a player, see if the player has enough mana
	if (isCharacter)
	{
		AMobaCharacter* PlayerCharacter = dynamic_cast<AMobaCharacter*>(this->GetCaster()); //cast to MobaCharacter so mana can be checked
		if (PlayerCharacter->GetMana() < ManaCost)
		{
			UE_LOG(LogTemp, Warning, TEXT("You don't have enough mana to cast that spell (Current Mana: %f)"), PlayerCharacter->GetMana());
			return false;
		}
	}
	return true;
}


void UAbilityComponent::CastAbility_Implementation()
{
}

void UAbilityComponent::CastProjectile()
{
	//Present for debug purposes
	//UE_LOG(LogTemp, Warning, TEXT("Successfully cast!"));

	//calculating the to-be-spawned AbilityProjectile's spawn and destination locations
	FVector
		Start = GetCaster()->GetActorLocation() + ProjectileRelativeSpawnLocation;
	FRotator Rotation = GetCaster()->GetActorRotation();
	//radian input!
	/*float
		Sin = FGenericPlatformMath::Sin(Rotation.Yaw / 180 * PI),
		Cos = FGenericPlatformMath::Cos(Rotation.Yaw / 180 * PI);*/

	/*Start.X += ProjectileRelativeSpawnLocation.X * Cos;
	Start.Y += ProjectileRelativeSpawnLocation.Y * Sin;
	Start.Z += ProjectileRelativeSpawnLocation.Z;*/

	FRotator Rot = FRotationMatrix::MakeFromX(FVector(TargetLocation, 0) - Start).Rotator();

	AAbilityProjectile *Projectile = (AAbilityProjectile*)(GetWorld()->SpawnActor(AbilityProjectileClass, &Start, &Rot));
	Projectile->SetSource(GetCaster());

	if (bTargetedAbility)
	{
		Projectile->SetDestination(TargetActor);
	}
	else
	{
		/*Destination.X = Start.X - MaxRange * Cos;
		Destination.Y = Start.Y + MaxRange * Sin;
		Destination.Z = Start.Z;*/
		//(GetWorld()->SpawnActor(AbilityProjectileClass, &Start, &Rotation));
		Projectile->SetDestination(TargetLocation);// FVector(TargetLocation.X, TargetLocation.Y, 200));
	}
}

AInteractable * UAbilityComponent::GetCaster() const
{
	return (AInteractable*)GetOwner();
}

/*
	----------
	Target related functions
	----------
*/
void UAbilityComponent::SetTargetParameters(bool bTargeted, bool bPlayer, bool bCreep, bool bStructure, bool bLocation, bool bAlly, bool bEnemy, bool bNeutral)
{
	this->bTargetedAbility = bTargeted;
	this->bPlayerValidTarget = bPlayer;
	this->bCreepValidTarget = bCreep;
	this->bStructureValidTarget = bStructure;
	this->bLocationValidTarget = bLocation;
	this->bAllyValidTarget = bAlly;
	this->bEnemyValidTarget = bEnemy;
	this->bNeutralValidTarget = bNeutral;
}

void UAbilityComponent::SetTarget(TWeakObjectPtr<AActor> DirectTarget, FVector2D Location)
{
	TargetActor = DirectTarget;
	TargetLocation = Location;
}

bool UAbilityComponent::IsTargetValid()
{
	/*
	This code directly checks if TargetActor is a valid target.
	If the TargetActor does not qualify as a valid target
	or if a TargetActor does not exist at the TargetedLocation,
	this function will return true if the targeted location is considered a valid target.
	Otherwise, this function will return false.

	A Traget is valid iff:
	(1) It is of proper type 
	(2) It shares a proper relationship with the caster
	(3) If either of these conditions fails, this funtion will return true if targeted locations are considered valid targets.

	Control flow:
	Do we care about having a Target?
	Is the Target still there?
	Is the Target of a type we are actually targeting?
	Does the Target share a proper relationship with the Caster?
	*/

	//trivially return true if this Ability is not a targeted Ability
	if (!bTargetedAbility)
	{
		return true;
	}

	/* If TargetActor doesn't point to a 'live' UObject (such as if no Actor exists at the TargetLocation),
	it cannot possibly be a valid. This leaves only the possibility of a location being valid. */
	if (!TargetActor.IsValid())
	{
		UE_LOG(Abilities, Warning, TEXT("AbilityComponent.cpp/IsTargetValid(): TargetActor does not exist/pointer is null."));
		return bLocationValidTarget;
	}

	/*
	Checking to see if TargetActor is of a type that is potentially targetable (a subclass of Interactable).
	Whether a particular subclass of Interactable is an actual tragetable type is dependent on its associated boolean values.
	All other types are automatically disqualified of validity.
	*/

	//if TargetClass is not a subclass of Interactable, it is automatically disqualified
	const UClass *TargetClass = TargetActor.Get()->GetClass();
	if (!TargetClass->IsChildOf(AInteractable::StaticClass()))
	{
		return bLocationValidTarget;
	}

	const AInteractable *TargetInteractable = (AInteractable*)TargetActor.Get();
	const bool bPlayer = TargetInteractable->IsPlayer(),
		bCreep = TargetInteractable->IsCreep(),
		bStructure = TargetInteractable->IsStructure();

	if(!(
		(bPlayer && bPlayerValidTarget) ||
		(bCreep && bCreepValidTarget) ||
		(bStructure && bStructureValidTarget)
		))
	{
		return bLocationValidTarget;
	}

	//If TargetActor shares a proper relationship with Caster, Target is concluded to be valid.
	//If TargetActor is valid, audjusting TargetLocation to be exactly that of the TargetActor.
	ERelationship Relationship = AInteractable::GetRelationship(GetCaster(), TargetActor.Get());
	if (
		(bAllyValidTarget && Relationship == ERelationship::Ally) ||
		(bEnemyValidTarget && Relationship == ERelationship::Enemy) ||
		(bNeutralValidTarget && Relationship == ERelationship::Neutral)
		)
	{
		TargetLocation = FVector2D(TargetActor.Get()->GetActorLocation());
		return true;
	}
	
	//All direct checks have been made. If Target is still not of valid type, Location is the last result.
	return bLocationValidTarget;
}

bool UAbilityComponent::IsTargetInRange() const
{
	UE_LOG(Abilities, Log, TEXT("Still have yet to make RANGE_SELF and RANGE_GLOBAL available in Blueprints."));

	FVector2D CasterLocation = FVector2D(GetCaster()->GetActorLocation());

	return 
		MaxRange == RANGE_SELF ||
		MaxRange == RANGE_GLOBAL ||
		FVector2D::Distance(CasterLocation, TargetLocation) <= MaxRange;
}

void UAbilityComponent::onAbilityEnd(UObject* instigator) {
	if(activeEvo)
		activeEvo->onEndTrigger(instigator);
}

void UAbilityComponent::skillUp(uint8 newRank) {
	if (activeEvo)
		activeEvo->SkillUp(newRank);
}