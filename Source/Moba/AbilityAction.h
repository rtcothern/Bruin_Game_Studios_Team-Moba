// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "AbilityAction.generated.h"

UENUM()
enum EventMessage {
	//actor onX methods
	ACTOR_BEGIN_OVERLAP,
	ACTOR_END_OVERLAP,
	ACTOR_HIT,
	BEGIN_CURSOR_OVER,
	CLICKED,
	DESTROYED,
	END_CURSOR_OVER,
	END_PLAY,
	INPUT_TOUCH_BEGIN,
	INPUT_TOUCH_END,
	INPUT_TOUCH_ENTER,
	INPUT_TOUCH_LEAVE,
	RELEASED,
	TAKE_ANY_DAMAGE,
	TAKE_POINT_DAMAGE,

	//additional component onX methods
	COMPONENT_BEGIN_OVERLAP,
	COMPONENT_END_OVERLAP,
	COMPONENT_HIT,
	COMPONENT_SLEEP,
	COMPONENT_WAKE,

	//action related events
	START
};

//forward class declaration to prevent circular dependencies
class UAbilityComponent;

/**
 * 
 */
UCLASS(NotBlueprintable)
class MOBA_API UAbilityAction : public UObject
{
	GENERATED_BODY()
private:
	UWorld* GetWorld() const;
	//streamline function used to aid spawning

	//UPROPERTY()
	TMap<EventMessage, TArray<UAbilityAction*>> mBroadcastTargets;
	//
	//12345: fear of garbage collection no collecting, don't know if UPROPERTY support yet

	UPROPERTY()
	UAbilityComponent* mParent;
	//12345: make const
	//the ability this action belongs to

	UPROPERTY()
	UClass* mCosmeticActorClass;
	//the class to be instantiated when this action is ready to spawn its cosmetic actor

	UPROPERTY()
	AActor* mCosmeticActor;
	//instance of 

public:
	/*** Constructors ***/
	UAbilityAction();
	//UObject requires this to be declared

	/*** ***/
	void SetParent(UAbilityComponent *parent);
	//

	void SetCosmeticActorClass(UClass *type);
	//

	void AddOutput(UAbilityAction* action, const EventMessage condition);
	//

	bool OutputsTo(const UAbilityAction* action, const EventMessage condition);
	//returns true if action broadcasts to action during some event

	/*** ***/
	void BroadcastEvent(const EventMessage condition);
	//

	void ReceiveEvent(const UAbilityAction* broadcaster, const EventMessage condition);
	//
	
	void Start();
	//begins executing the action

	/*** Overloads ***/
	UFUNCTION()
	void OnActorBeginOverlap(AActor* other);
	//
};