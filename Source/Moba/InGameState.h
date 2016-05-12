// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "Interactable.h"
#include "InGameState.generated.h"

/**
*
*/
UCLASS()
class MOBA_API AInGameState : public AGameState
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, Replicated)
	int32 team1Level;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int32 team2Level;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int32 team1Xp;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int32 team2Xp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 xpPerLevel;

public:
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category="Experience")
	void GainExperience(ETeam team, int32 xpGained);
	//Awards passed team experience
	//validation function makes sure team is TeamA or TeamB

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "Experience")
	void LevelUp(ETeam team);
	//increments passed team's level
	//validation function makes sure team is TeamA or TeamB

	AInGameState(const class FObjectInitializer& PCIP);
};
