// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* owningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(owningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	APlayerController* PC =  Ability->GetCurrentActorInfo()->PlayerController.Get();

	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);
	ValidData.Broadcast(CursorHit.Location);
}
