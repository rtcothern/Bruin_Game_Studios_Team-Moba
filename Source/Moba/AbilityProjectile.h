// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "AbilityComponent.h"
#include "AbilityProjectile.generated.h"

UCLASS()
class MOBA_API AAbilityProjectile : public AActor
{
	GENERATED_BODY()
protected:
	//Object in charge of moving the projectile through the world
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "")
	UProjectileMovementComponent *MovementComponent;

	//the location where the projectile will terminate
	/*UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "")
	FVector2D Destination;*/

	//the speed in Units/second
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "")
	float Velocity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "")
	float Time;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "")
	bool bIsTargeted;

	//The actual distance the projectile will move each second
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "")
	FVector Delta;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	AInteractable *Source;

public:	
	// Sets default values for this actor's properties
	AAbilityProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//
	void SetDestination(FVector2D Dest, float MaxRange);

	void SetDestination(TWeakObjectPtr<AActor> destActor);

	//Updates Velocity and recalculates Delta
	UFUNCTION(BlueprintCallable, Category = "")
	void SetVelocity(float InVelocity);

	//
	void SetSource(AInteractable *s);

	UFUNCTION(BlueprintNativeEvent, Category = "Projectile Actions")
		void spawnAOE();

	/*
	//
	//UFUNCTION()
	UAbilityComponent* GetAbility();

	//
	//UFUNCTION()
	void SetAbility();
	*/
};
