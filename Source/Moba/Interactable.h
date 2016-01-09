// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Interactable.generated.h"

UCLASS()
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

	//
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsPlayer();

	//
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsMinion();

	//
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual bool IsStructure();
};
