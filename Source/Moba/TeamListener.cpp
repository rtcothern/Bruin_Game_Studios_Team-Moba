// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "TeamListener.h"


// Sets default values
ATeamListener::ATeamListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeamListener::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeamListener::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATeamListener::acquireExp(int32 amount) {

}
void ATeamListener::notifyLevelUp() {
	for (AInteractable* i : subjects) {
		
	}
}
void ATeamListener::registerSubject(AUnit* newSub) {

}


