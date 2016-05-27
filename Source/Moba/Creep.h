// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unit.h"
#include "Creep.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API ACreep : public AUnit
{
	GENERATED_BODY()
	
	bool IsCreep() const override final { return true; };
	
};
