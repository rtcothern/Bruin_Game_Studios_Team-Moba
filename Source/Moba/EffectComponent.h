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
		//
		UFUNCTION(BlueprintNativeEvent)
		void Initialize();

		//
		UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		float Duration;

	public:	
		// Sets default values for this component's properties
		UEffectComponent();

		// Called when the game starts
		virtual void BeginPlay() override;
	
		// Called every frame
		virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		//Initial tasks to be executed when after EffectComponent has been applied
		UFUNCTION(BlueprintNativeEvent, Category = "Effect")
		void OnApply();		
};
