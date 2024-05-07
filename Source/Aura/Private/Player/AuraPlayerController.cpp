// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include"EnhancedInputComponent.h"
#include"EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	
}
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);

	if (!CursorHit.bBlockingHit) return;

	LastActor = CurActor;
	CurActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (LastActor == nullptr)
	{
		if (CurActor !=nullptr)
		{
			CurActor->HiglightActor();
		}
	}
	//上一个对象存在
	else
	{
		
		if (CurActor !=nullptr)
		{
			if (CurActor != LastActor)
			{
				CurActor->HiglightActor();
				LastActor->UnHelightActor();
			}
		}
		else
		{
			LastActor->UnHelightActor();
		}
	}

	
}


void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	//对不同的context进行排序
	Subsystem->AddMappingContext(AuraContext,0);

	bShowMouseCursor = true;

	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	inputModeData.SetHideCursorDuringCapture(false);
	//实际设置过程
	SetInputMode(inputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInputComponent =CastChecked<UEnhancedInputComponent>(InputComponent);

	enhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D inputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator rotation = GetControlRotation();
	const FRotator YawRotator(0.f,rotation.Yaw,0.f);

	//获取世界坐标下的向量，X为世界正方向
	const FVector ForwardDirction = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

	//在可运行物体存在的情况下才会进行处理
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirction,inputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection,inputAxisVector.X);
	}
}

