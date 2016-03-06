// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "AbilityBuilder.generated.h"

class UAbilityComponent;
class UAbilityAction;
enum EventMessage;

/**
 * 
 */
UCLASS()
class MOBA_API UAbilityBuilder : public UObject
{
	GENERATED_BODY()
private:
	//12345: make this static?
	TMap<FString, UClass*> assets;
	//

	UAbilityComponent *mAbility;
	//

	TMap<FString, UAbilityAction*> mActionMap;
	//

	UAbilityBuilder& AddAction(const FString& name);
	//adds a new action to the map with actionName key

	UAbilityBuilder& AddOutput(const FString& from, const FString& to, const EventMessage when);
	//

	UAbilityBuilder& SetCosmeticActorClass(const FString& actionKey, const FString& assetKey);
	//

	UAbilityComponent* Build();
	//
public:
	//12345: AInteractable, AUnit, etc?
	UFUNCTION(BlueprintCallable, Category = "Ability Creation")
	static UAbilityComponent* BuildAbility(AInteractable* owner, int32 baseAbilityId, int32 evolutionId, int32 skillRank);
	//	

	UAbilityBuilder();
	//adds default root component	
};
