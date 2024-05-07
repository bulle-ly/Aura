// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraBaseCharacter.h"
#include"Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraBaseCharacter,public IEnemyInterface
{
	GENERATED_BODY()
public:
	virtual void HiglightActor() override;
	virtual void UnHelightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHightLighted = false;
};
