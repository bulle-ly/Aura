// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"


#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0,400,0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//忽略掉角色的旋转和摄像机的关系
	bUseControllerRotationPitch= false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


}
void AAuraCharacter::OnRep_PlayerState()
{
	//for Client
	Super::OnRep_PlayerState();
	InitAbilityInfo();
}
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//for Server
	InitAbilityInfo();
}

void AAuraCharacter::InitAbilityInfo()
{
	//AController* AuraPlayerController =GetController();
	//AAuraPlayerState* AuraPlayerState = AuraPlayerController->GetPlayerState<AAuraPlayerState>();
	//PossessedBy 中的State在时间点内没有填充
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	//在角色进行初始化的情况下进行set的delegate绑定
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->InitAbilityInfoSet();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	if(AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AURAHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AURAHUD->InitOverlay(AuraPlayerController,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
	}
}



