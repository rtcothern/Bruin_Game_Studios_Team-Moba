// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Moba.h"
#include "MobaCharacter.h"
#include "Unit.h"
#include "AbilityComponent.h"
#include "MobaPlayerController.h"
#include "MobaAIController.h"
#include "AI/Navigation/NavigationSystem.h"

AMobaPlayerController::AMobaPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	//DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMobaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AMobaPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMobaPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMobaPlayerController::OnSetDestinationReleased);
	InputComponent->BindAction("CastAbility1", IE_Released, this, &AMobaPlayerController::CastAbility1);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMobaPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMobaPlayerController::MoveToTouchLocation);
}

void AMobaPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)

	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AMobaPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AMobaPlayerController::SetNewMoveDestination_Implementation(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AMobaPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMobaPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AMobaPlayerController::CastAbility1_Implementation()
{
	/*AMobaCharacter *Character = (AMobaCharacter*)(PlayerAIController->GetCharacter());
	FHitResult Result;
	GetHitResultUnderCursor(ECC_Visibility, false, Result);
	Character->AMobaCharacter::CastAbility(EKeyToAbilityIndex::Q, Result.Actor, FVector2D(Result.Location));*/
} //why do I need to be explicit with what version of CastAbility I'm calling?
  //If the function is not virtual(castAbility, declared in unit.h), it works as expected
  //If it is virtual, I need to include "AUnit::", or, in this case, "AMobaCharacter::"

bool AMobaPlayerController::CastAbility1_Validate() {
	return true;
}