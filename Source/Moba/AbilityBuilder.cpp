// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "AbilityBuilder.h"
#include "AbilityAction.h"
#include "AbilityComponent.h"

UAbilityBuilder::UAbilityBuilder() {
	//12345: still haven't found anything cleaner
	static ConstructorHelpers::FObjectFinder<UBlueprint>
		Bolt(TEXT("Blueprint'/Game/TopDownCPP/Blueprints/Bolt.Bolt'"));
	assets.Add("Bolt", Bolt.Object->GetBlueprintClass());

	mAbility = NewObject<UAbilityComponent>(this->GetOuter(), UAbilityComponent::StaticClass());
	AddAction("root");
	mAbility->SetRoot(*mActionMap.Find("root"));
}

UAbilityComponent* UAbilityBuilder::BuildAbility(AInteractable* owner, int32 baseAbilityId, int32 evolutionId, int32 skillRank) {
	//12345: currently only builds bolt ability
	UAbilityBuilder *builder = NewObject<UAbilityBuilder>((UObject*)owner, UAbilityBuilder::StaticClass());
	(*builder).AddAction("cast_projectile")
		.SetCosmeticActorClass("cast_projectile", "Bolt")
		.AddOutput("root", "cast_projectile", START);

	return builder->Build();
}

UAbilityComponent* UAbilityBuilder::Build() {
	//setting the parent of all the actions
	TMap<FString, UAbilityAction*>::TIterator it = mActionMap.CreateIterator();
	for (; bool(it); ++it)
		it.Value()->SetParent(mAbility);

	return mAbility;
}

UAbilityBuilder& UAbilityBuilder::AddAction(const FString& name) {
	UAbilityAction *action = NewObject<UAbilityAction>();
	action->SetParent(mAbility);
	mActionMap.Add(name, action);
	return *this;
}

UAbilityBuilder& UAbilityBuilder::AddOutput(const FString& from, const FString& to, const EventMessage when) {
	//can't add output if one of the keys is not found in the map
	if (!mActionMap.Contains(from) || !mActionMap.Contains(to)) return *this;

	UAbilityAction *leader = mActionMap.FindRef(from),
		*follower = mActionMap.FindRef(to);

	//preventing circular reference
	if (!follower->OutputsTo(leader, when)) {
		leader->AddOutput(follower, when);
	}

	return *this;
}

UAbilityBuilder& UAbilityBuilder::SetCosmeticActorClass(const FString& actionKey, const FString& assetKey) {
	//make sure both passed keys are mapped
	if (!mActionMap.Contains(actionKey) || !assets.Contains(assetKey)) return *this;
	mActionMap.FindRef(actionKey)->SetCosmeticActorClass(assets.FindRef(assetKey));
	return *this;
}


