// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Moba.h"
#include "MobaCharacter.h"

float counter = 0.0; ///DEBUG PURPOSES ONLY

AMobaCharacter::AMobaCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

bool AMobaCharacter::IsPlayer() const
{
	return true;
}


void AMobaCharacter::acquireAbility(UClass * abilityType) {
	UAbilityComponent* pComponent = NewObject<UAbilityComponent>(this, abilityType);
	pComponent->RegisterComponent();

	//Abilities[(int32)EKeyToAbilityIndex::Q] = pComponent;
	int index = Abilities.Add(pComponent);
	UE_LOG(LogTemp, Log, TEXT("AbilityComponent.cpp/SetTarget(): %d"), index);

}

void AMobaCharacter::CastAbility(EKeyToAbilityIndex Key, TWeakObjectPtr<AActor> TargetActor, FVector2D TargetLocation)
{
	if (Abilities.Num() > (int32)Key) {
		Abilities[(int32)Key]->SetTarget(TargetActor, TargetLocation);

		bool success = Abilities[(int32)Key]->AttemptCast();
		if (success) //if the ability was cast, the player uses mana
			LoseMana(Abilities[(int32)Key]->GetManaCost());
	}

}

// Called every frame
void AMobaCharacter::Tick(float DeltaTime)
{
	////To-Do: Change what happens during a tick if the player is dead
	//if (Dead)
	//	; //do something else

	Super::Tick(DeltaTime);
	RegenMana(DeltaTime);

	///DEBUG PURPOSES ONLY
	///Prints out to log an update on mana every second
	counter += DeltaTime;
	if (counter > 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Your character has %f mana."), RemainingMana);
		counter = 0;
	}
	

}

float AMobaCharacter::LoseMana(float LoseManaAmount)
{
	RemainingMana -= LoseManaAmount;

	if (RemainingMana < 0)
		RemainingMana = 0;

	return RemainingMana;
}


void AMobaCharacter::RegenMana(float RegenModifier) //Normally, RegenModifier will be DeltaTime
{   //Make a more elegant solution?
	if (RemainingMana < MaxMana)
		RemainingMana += (ManaRegenRatePerSecond * RegenModifier); //Converts regen rate from mana per second to mana per DeltaTime
	if (RemainingMana > MaxMana)
		RemainingMana = MaxMana;
}

float AMobaCharacter::GetMana()
{
	return RemainingMana;
}

bool AMobaCharacter::IsDead()
{
	return Dead;
}

void AMobaCharacter::SetDead()
{
	Dead = true; //to be changed back to false through respawn mechcanic

	//Check to see if any experience should be rewarded based on the character dying
	AttemptToGiveEnemyExperience();
}

void AMobaCharacter::AttemptToGiveEnemyExperience_Implementation()
{

}