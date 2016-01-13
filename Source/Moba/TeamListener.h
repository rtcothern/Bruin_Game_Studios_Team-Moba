// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Unit.h"
#include "TeamListener.generated.h"

UCLASS()
class MOBA_API ATeamListener : public AActor
{
	GENERATED_BODY()
	
private:
	TArray<AUnit*> subjects;
public:	
	// Sets default values for this actor's properties
	ATeamListener();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Team Listener")
		void acquireExp(int32 amount);
	UFUNCTION(BlueprintCallable, Category = "Team Listener")
		void notifyLevelUp();
	UFUNCTION(BlueprintCallable, Category = "Team Listener")
		void registerSubject(AUnit* newSub);
};
