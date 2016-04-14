// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "Evo.h"

UEvo::UEvo() {
	skillPoints = 0;
	ownerAbility = Cast<UAbilityComponent>(GetOuter());
}
 void UEvo::onEndTrigger() {
	 for (int i = 0; i < skillPoints; i++) {
		 EvoSkills[i]->attemptExecuteTrigger(UEvo::EEvoTrigger::EE_End);
	 }
 };
 void UEvo::SkillUp(uint8 newRank) { 
	 if (newRank >= 0 && newRank <= 3 && EvoSkills[newRank]->onAcquire != nullptr)
		 EvoSkills[newRank]->onAcquire(ownerAbility);
	 skillPoints = newRank;
 }