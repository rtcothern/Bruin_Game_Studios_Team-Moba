// Fill out your copyright notice in the Description page of Project Settings.

#include "Moba.h"
#include "Evo.h"

void UEvo::execute() {
	switch (skillPoints) {
	case 0:
		applySkill0();
	case 1:
		applySkill1();
	case 2: 
		applySkill2();
	case 3:
		applySkill3();
	}
}
