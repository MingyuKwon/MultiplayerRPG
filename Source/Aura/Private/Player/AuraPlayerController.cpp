// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Interaction/EnemyInterface.h"
#include "Input/AuraInputComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponentBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SplineComponent.h"
#include "AuraGameplayTags.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext); // AuraContext가 null인지 아닌지 여기서 체크하고 아니라면 크래시

	//SubSystem는 싱글톤이어서 딱 하나만 존재한다
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem != nullptr)
	{
		SubSystem->AddMappingContext(AuraContext, 0);
	}

	// 게임 중에 마우스 커서 보이도록 하고, 기본 마우스 커서 모양으로 정함
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

	UAuraInputComponent* auraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	auraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	auraInputComponent->BindAbilityActions(InputConfig, this, 
		&AAuraPlayerController::AbilityInputTagPressed, 
		&AAuraPlayerController::AbilityInputTagReleased,
		&AAuraPlayerController::AbilityInputTagHeld);


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


	// last와 current 가 둘다 null인 경우 -> 아무것도 안함

	// last가 null,  current 가 null이 아닌 경우 -> current hilight

	// last가 null이 아닌 경우,  current 가 null인 경우 -> unhilight last

	// last와 current 가 둘다 null이 아닌 경우
	//		last 와 current가 같은 경우 -> 현재 유지
	
	//		last 와 current가 다른 경우 -> last unhilight current highlight

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

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag inputTag)
{
	if (inputTag.MatchesTagExact(FAuraGamplayTags::Get().InputTag_LMB))
	{
		if (CurrentActor)
		{
			bisTargeting = true;
		}
		else
		{
			bisTargeting = false;
		}

		bAutoRunning = false;
	}
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag inputTag)
{
	if (!inputTag.MatchesTagExact(FAuraGamplayTags::Get().InputTag_LMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(inputTag);
		}

		return;
	}

	if (bisTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(inputTag);
		}
	}
	else
	{
		APawn* ControlledPawn = GetPawn();
		if (followTime <= ShortPressThreshHold)
		{
			if (UNavigationPath* NavPath = 
				UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& points : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(points, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), points, 8.f, 8, FColor::Red , false, 5.f);
				}

				bAutoRunning = true;
				
			}
			
		}

		followTime = 0.f;
		bisTargeting = false;
	}

}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag inputTag)
{
	if (!inputTag.MatchesTagExact(FAuraGamplayTags::Get().InputTag_LMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(inputTag);
		}

		return;
	}
	
	if (bisTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(inputTag);
		}
	}
	else
	{
		followTime += GetWorld()->GetDeltaSeconds();

		FHitResult Hit;
		if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
	
	
}

UAuraAbilitySystemComponentBase* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (AbilitySystemComponent == nullptr)
	{
		AbilitySystemComponent = Cast<UAuraAbilitySystemComponentBase>
			(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}

	return AbilitySystemComponent;
}
