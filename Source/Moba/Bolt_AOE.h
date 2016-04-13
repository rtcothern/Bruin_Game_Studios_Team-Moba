// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Evo.h"
#include "Bolt_AOE.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API UBolt_AOE : public UEvo
{
	GENERATED_BODY()
protected:
	virtual void applySkill0();
	virtual void applySkill1();
	virtual void applySkill2();
	virtual void applySkill3();

public:	
	UBolt_AOE();
};
