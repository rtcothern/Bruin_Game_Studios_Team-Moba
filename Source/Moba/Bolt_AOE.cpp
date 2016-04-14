// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "Bolt_AOE.h"

UBolt_AOE::UBolt_AOE() :Super() {
	EvoSkill* skill0 = new EvoSkill(this, "AOE",
		"Bolt pierces instead of stopping on first target hit",
		{ [](UAbilityComponent* owner) { owner->SetProjectilePierces(true); } });

	EvoSkill* skill1 = new EvoSkill(this, "Juggernaut",
		"Bolt grows in size",
		{ [](UAbilityComponent* owner) { owner->SetProjectileSize(owner->GetProjectileSize() + 10); } });

	EvoSkill* skill2 = new EvoSkill(this, "?", "?", nullptr);

	EvoSkill* skill3 = new EvoSkill(this, "Thunderlord", "Bolt explodes upon reaching it's destination", nullptr);

	EvoSkills.Add(skill0);
	EvoSkills.Add(skill1);
	EvoSkills.Add(skill2);
	EvoSkills.Add(skill3);
}


