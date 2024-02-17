// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Interaction/EnemyInterface.h"



AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext); // AuraContext�� null���� �ƴ��� ���⼭ üũ�ϰ� �ƴ϶�� ũ����

	//SubSystem�� �̱����̾ �� �ϳ��� �����Ѵ�
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem != nullptr)
	{
		SubSystem->AddMappingContext(AuraContext, 0);
	}

	// ���� �߿� ���콺 Ŀ�� ���̵��� �ϰ�, �⺻ ���콺 Ŀ�� ������� ����
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;


	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirecton = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	APawn* ControlledPawn = GetPawn<APawn>();
	if (ControlledPawn)
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirecton, InputAxisVector.X);
	}
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult hitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);

	if (!hitResult.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = Cast<IEnemyInterface>(hitResult.GetActor());


	// last�� current �� �Ѵ� null�� ��� -> �ƹ��͵� ����

	// last�� null,  current �� null�� �ƴ� ��� -> current hilight

	// last�� null�� �ƴ� ���,  current �� null�� ��� -> unhilight last

	// last�� current �� �Ѵ� null�� �ƴ� ���
	//		last �� current�� ���� ��� -> ���� ����
	
	//		last �� current�� �ٸ� ��� -> last unhilight current highlight

	if (LastActor == nullptr)
	{
		if (CurrentActor == nullptr)
		{
			// Do nothing
		}
		else
		{
			// current highlight
			CurrentActor->HighlightActor();
		}
	}
	else
	{
		if (CurrentActor == nullptr)
		{
			// unhighlight last
			LastActor->UnHighlightActor();
		}
		else
		{
			if (CurrentActor == LastActor)
			{
				CurrentActor->HighlightActor();
			}
			else
			{
				LastActor->UnHighlightActor();
				CurrentActor->HighlightActor();
			}
		}
	}

}
