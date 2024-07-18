// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraBaseCharacter.h"
#include"Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"


class UAuraAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraBaseCharacter,public IEnemyInterface
{
	GENERATED_BODY()
public:

	/** Enemy InterFace*/
	virtual void HiglightActor() override;
	virtual void UnHelightActor() override;

	/** End Enemy Interface */

	virtual void BeginPlay() override;
	AAuraEnemy();
	virtual  void InitAbilityInfo() override;
};
