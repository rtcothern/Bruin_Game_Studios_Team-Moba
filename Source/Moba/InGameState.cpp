// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "InGameState.h"
#include "UnrealNetwork.h"

AInGameState::AInGameState(const class FObjectInitializer & PCIP) : Super(PCIP) {
	bReplicates = true;
}

void AInGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	DOREPLIFETIME(AInGameState, team1Level);
	DOREPLIFETIME(AInGameState, team2Level);
	DOREPLIFETIME(AInGameState, team1Xp);
	DOREPLIFETIME(AInGameState, team2Xp);
}

void AInGameState::GainExperience_Implementation(ETeam team, int32 xpGained) {
	int32& passedTeamXp = team == ETeam::TeamA ? team1Xp : team2Xp;
	passedTeamXp += xpGained;
	if (passedTeamXp >= xpPerLevel) {
		LevelUp(team);
	}
}

bool AInGameState::GainExperience_Validate(ETeam team, int32 xpGained) {
	return team == ETeam::TeamA || team == ETeam::TeamB;
}

void AInGameState::LevelUp_Implementation(ETeam team) {
	if (team == ETeam::TeamA) {
		if (team1Xp >= xpPerLevel) {
			team1Level++;
			team1Xp -= xpPerLevel;
		}
	}
	else {
		if (team2Xp >= xpPerLevel) {
			team2Level++;
			team2Xp -= xpPerLevel;
		}
	}
}

bool AInGameState::LevelUp_Validate(ETeam team) {
	return team == ETeam::TeamA || team == ETeam::TeamB;
}