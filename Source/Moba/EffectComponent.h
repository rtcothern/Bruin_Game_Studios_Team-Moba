// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "EffectComponent.generated.h"


/**
Effect Components affect targets in a singular way;
they are responsible for no more.
For Example, say an Effect Component deals damage.
The Effect should only inflict damage.
It is up to the afflicted target to determine if it is dead.
*/
UCLASS(Blueprintable, BlueprintType, ClassGroup = "Effects")
class MOBA_API UEffectComponent : public UActorComponent
{
	GENERATED_BODY()

	protected:
		//how long this effect will remain attatched to its target
		UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		float Duration;

		//what the component does every tick
		//delta is the amount of time which has passed
		UFUNCTION(BlueprintNativeEvent)
		void Persist(float delta);

		//cleanup to be preformed before destroy the component
		//consider restoring the owning actor to its original state
		UFUNCTION(BlueprintNativeEvent)
		void Cleanup();

	public:	
		// Sets default values for this component's properties
		UEffectComponent();

		// Called when the game starts
		virtual void BeginPlay() override;
	
		// Called every frame
		virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		//what must be done immediately upon attaching this EffectComponent to an Interactable
		//it is advised that you set duration in 
		UFUNCTION(BlueprintNativeEvent)
		void Apply();

		//returns who this ability is attached to
		UFUNCTION(BlueprintCallable, Category = "Effects")
		AInteractable* GetAffected() const;

		//
		UFUNCTION(BlueprintCallable, Category = "Effects")
		AInteractable* GetCaster() const;
		
};
