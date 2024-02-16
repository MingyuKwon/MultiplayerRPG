// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("SpringArm")));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Camera")));
	CameraComponent->SetupAttachment(SpringArmComponent);
		
	SpringArmComponent->TargetArmLength = 700.f;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// InitAbility actor info for the Server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// InitAbility actor info for the Client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* auraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(auraPlayerState);

	AbilitySystemComponent = auraPlayerState->GetAbilitySystemComponent();
	AttributeSet = auraPlayerState->GetAttributeSet();

	AbilitySystemComponent->InitAbilityActorInfo(auraPlayerState, this);

	AAuraPlayerController* playerController = Cast<AAuraPlayerController>(GetController());
	if (playerController != nullptr)
	{
		AAuraHUD* auraHud = Cast<AAuraHUD>(playerController->GetHUD());
		if (auraHud != nullptr)
		{
			auraHud->InitOverlay(playerController, auraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	
}
