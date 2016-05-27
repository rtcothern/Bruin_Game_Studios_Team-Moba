// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "AbilityProjectile.h"


// Sets default values
AAbilityProjectile::AAbilityProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(RootComponent);
	MovementComponent->SetPlaneConstraintEnabled(true);
	MovementComponent->SetPlaneConstraintNormal(FVector(0.f, 0.f, 1.f));

	bIsTargeted = false;
	Time = 0;
}

// Called when the game starts or when spawned
void AAbilityProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbilityProjectile::Tick( float DeltaTime )
{
	if (!bIsTargeted) {
		Time -= DeltaTime;
		if (Time < 0) {
			Destroy();
		}
	}
	Super::Tick( DeltaTime );
}

void AAbilityProjectile::SetDestination(FVector2D Dest, float MaxRange)
{
	//Destination = Dest;
	float Distance = FVector2D::Distance(
		FVector2D(GetActorLocation()),
		FVector2D(Dest)
		);
	Distance = Distance > MaxRange ? MaxRange : Distance;
	Time = Distance / Velocity;
	bIsTargeted = false;


	/*Delta = FVector(Dest - FVector2D(GetActorLocation()), 0);
	Delta.X /= Time;
	Delta.Y /= Time;*/
	//SetVelocity(Velocity);
	//MovementComponent->SetVelocityInLocalSpace(Delta);
}

void AAbilityProjectile::SetDestination(TWeakObjectPtr<AActor> destActor) {
	MovementComponent->HomingTargetComponent = destActor->GetRootComponent();
	bIsTargeted = true;
}

//Deprecated
void AAbilityProjectile::SetVelocity(float InVelocity)
{
	/*Velocity = InVelocity;

	float Distance = FVector2D::Distance(
		FVector2D(GetActorLocation()),
		FVector2D(Destination)
		);

	float Time = Distance / Velocity;

	Delta = Destination - GetActorLocation();
	Delta.X /= Time;
	Delta.Y /= Time;
	Delta.Z = 0;*/
}

void AAbilityProjectile::SetSource(AInteractable * s)
{
	Source = s;
}

void AAbilityProjectile::spawnAOE_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("Spawning aoe at Location: %s"),
		*this->GetActorLocation().ToString());
}