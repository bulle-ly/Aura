// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraBaseCharacter.generated.h"

UCLASS(Abstract)
class AURA_API AAuraBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//角色骨骼用于绑定武器
	UPROPERTY(EditAnywhere,Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	

};
 