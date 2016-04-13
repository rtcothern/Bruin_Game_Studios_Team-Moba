// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "Bolt_AOE.h"

UBolt_AOE::UBolt_AOE() {
	UEvo::UEvo();
	
	EvoSkill* skill0 = new EvoSkill("AOE", 
		"Bolt pierces instead of stopping on first target hit",
		{ [](UAbilityComponent* owner) { owner->SetProjectilePierces(true); } });
	EvoSkill* skill1 = new EvoSkill("Juggernaut", 
		"Bolt grows in size",
		{ [](UAbilityComponent* owner) { owner->SetProjectileSize(owner->GetProjectileSize() + 10); } });
	EvoSkill* skill2 = new EvoSkill("?", "?", nullptr);
	EvoSkill* skill3 = new EvoSkill("Thunderlord", "Bolt explodes upon reaching it's destination", nullptr);

	EvoSkills.Add(skill0);
	EvoSkills.Add(skill1);
	EvoSkills.Add(skill2);
	EvoSkills.Add(skill3);
}

void UBolt_AOE::applySkill0() {

}
void UBolt_AOE::applySkill1() {

}
void UBolt_AOE::applySkill2() {

}
void UBolt_AOE::applySkill3() {

}

