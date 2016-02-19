// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "MobaAIController.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API AMobaAIController : public AAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float MinimumMoveDist;
public:
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category="MobaAIController|Movement")
		void NetworkMove(FVector Destination);
	
};
