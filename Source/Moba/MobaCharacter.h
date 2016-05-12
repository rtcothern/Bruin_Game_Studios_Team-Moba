// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Unit.h"
#include "MobaCharacter.generated.h"

UCLASS(Blueprintable)
class AMobaCharacter : public AUnit
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	//RemainingMana = MaxMana upon respawn (not implemented)
	//This value should not change often nor outside of controlled situations (e.g. leveling up)...
	//... it is therefore recommended Getter/setters be used to change its value rather than direct manipulation.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MobaCharacter Stats")
		float MaxMana;

	//The amount of mana this MobaCharacter currently has
	//Temporary Implementation: Manually set this value to be the SAME VALUE as MaxMana in the BluePrints on Unreal
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MobaCharacter Stats")
	//DUPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "MobaCharacter Stats") -- needed after proper implementation 
		float RemainingMana;

	//The amount of mana to regenerate per second
	//To-Do: Implement different regen rates when inside vs outside of combat
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MobaCharacter Stats")
		float ManaRegenRatePerSecond;


public:
	AMobaCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	UFUNCTION(BlueprintCallable, Category = "Abilities")
		void acquireAbility(UClass * abilityType);
	//
	//UFUNCTION()
	void CastAbility(EKeyToAbilityIndex Key, TWeakObjectPtr<AActor> TargetActor, FVector2D TargetLocation) override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Lose a specified amount of mana
	virtual float LoseMana(float LoseManaAmount);

	//Regenerates Mana at the default regen rate (mana/sec) multiplied by the modifier value
	virtual void RegenMana(float RegenModifier);

	//Return the RemainingMana that a palyer has
	virtual float GetMana();

	bool IsPlayer() const override final;
	
};

