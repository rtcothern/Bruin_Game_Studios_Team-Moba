// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "AbilityComponent.h"
#include "Evo.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MOBA_API UEvo : public UObject
{
	GENERATED_BODY()
protected:
	
	enum EEvoTrigger : uint8 {
		EE_End UMETA(DisplayName = "On End")
	};
	typedef void (*SkillFunc)(UObject*);
	class EvoSkill {
		FString Name;
		FString Description;
	public:
		EvoSkill(UEvo* oEv, FString n, FString d, SkillFunc onAc) {
			Name = n;
			Description = d;
			onAcquire = onAc;
			ownerEvo = oEv;
			//4 being an arbitrary size for the moment, this will eventually be the number of triggers we can have
			triggers.Init(nullptr, 4);
		}

		//Associates the behavior with the given trigger index in the trigger array
		void setTriggerBehavior(EEvoTrigger t, SkillFunc behavior) {
			triggers[t] = behavior;
		}
		void attemptExecuteTrigger(EEvoTrigger t, UObject* instigator) {
			if (triggers[t] != nullptr)
				triggers[t](instigator);
		}
		SkillFunc onAcquire;
		TArray<SkillFunc> triggers;
		UEvo *ownerEvo;
	};
	
	UAbilityComponent* ownerAbility;
	int32 skillPoints;
	TArray<EvoSkill*> EvoSkills;
public:

	//No args Constructor required by Unreal for compilation
	UEvo();
	virtual void onEndTrigger(UObject* instigator);
	void SkillUp(uint8 newRank);

};
