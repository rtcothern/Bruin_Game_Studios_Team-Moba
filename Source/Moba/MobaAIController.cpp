// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "MobaAIController.h"

void AMobaAIController::NetworkMove_Implementation(FVector Destination) {
	ACharacter* c = GetCharacter();
	FVector loc = c->GetActorLocation();
	if (FVector::Dist(Destination, loc) > MinimumMoveDist) {
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		NavSys->SimpleMoveToLocation(this, Destination);
	}
}


bool AMobaAIController::NetworkMove_Validate(FVector Destination) {
	return true;
}


