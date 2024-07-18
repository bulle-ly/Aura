// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Aura.h"

void AAuraEnemy::HiglightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHelightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}


AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}

void AAuraEnemy::InitAbilityInfo()
{
	Super::InitAbilityInfo();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	//角色和目标的Abilitysystem必须是修改过的
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->InitAbilityInfoSet();
}



void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityInfo();
	
}
