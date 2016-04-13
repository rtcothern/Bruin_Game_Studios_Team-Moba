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
	typedef void (*SkillFunc)(UAbilityComponent*);
	class EvoSkill {
		FString Name;
		FString Description;
	public:
		EvoSkill(FString n, FString d, SkillFunc onAc) {
			Name = n;
			Description = d;
			onAcquire = onAc;
		}
		SkillFunc onAcquire;
	};
	
	UAbilityComponent* owner;
	int32 skillPoints;
	TArray<EvoSkill*> EvoSkills;
public:
	//Constructor required by Unreal for compilation
	UEvo() {
		skillPoints = 0;
		owner = nullptr;
	}
	UEvo(UAbilityComponent* own) {
		skillPoints = 0;
		owner = own;
	}
	virtual void applySkill0() {};
	virtual void applySkill1() {};
	virtual void applySkill2() {};
	virtual void applySkill3() {};

	virtual void execute();
};
