// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "AbilityAction.h"
#include "AbilityComponent.h"

/*** Constructors and Construction related functions ***/
UAbilityAction::UAbilityAction()
{
}

void UAbilityAction::AddOutput(UAbilityAction* action, const EventMessage condition) {
	TArray<UAbilityAction*>& conditionOutputs = mBroadcastTargets.FindOrAdd(condition);
	conditionOutputs.AddUnique(action);
}

void UAbilityAction::SetParent(UAbilityComponent* parent) {
	mParent = parent;
}
void UAbilityAction::SetCosmeticActorClass(UClass* type) {
	mCosmeticActorClass = type;
}

bool UAbilityAction::OutputsTo(const UAbilityAction* action, const EventMessage condition) {
	return mBroadcastTargets.Contains(condition) && mBroadcastTargets.FindRef(condition).Contains(action);
}
/*** ***/
void UAbilityAction::Start() {
	if (mCosmeticActorClass != nullptr) {
		mCosmeticActor = GetWorld()->SpawnActor(mCosmeticActorClass);
		mCosmeticActor->OnActorBeginOverlap.AddDynamic(this, &UAbilityAction::OnActorBeginOverlap);
	}

	BroadcastEvent(START);
}

void UAbilityAction::BroadcastEvent(const EventMessage condition) {
	//don't broadcast if no one wants to hear the message
	if (!mBroadcastTargets.Contains(condition)) return;

	TArray<UAbilityAction*> conditionOutputs = mBroadcastTargets.FindRef(condition);
	for (int index = 0; index < conditionOutputs.Num(); index++)
		conditionOutputs[index]->ReceiveEvent(this, condition);
}

void UAbilityAction::ReceiveEvent(const UAbilityAction *broadcaster, EventMessage condition) {
	//12345: what about multiple inputs?
	Start();
}

/*** Overloads ***/
void UAbilityAction::OnActorBeginOverlap(AActor* other) {
	BroadcastEvent(ACTOR_BEGIN_OVERLAP);
}

/*** Helpers ***/
UWorld* UAbilityAction::GetWorld() const {
	return mParent->GetOwner()->GetWorld();
}