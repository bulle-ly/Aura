// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraBaseCharacter.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraBaseCharacter
{
	GENERATED_BODY()

public: AAuraCharacter();

	virtual  void OnRep_PlayerState() override;
	virtual  void PossessedBy(AController* NewController) override;
	

private:
	virtual  void InitAbilityInfo()override;
	
};
