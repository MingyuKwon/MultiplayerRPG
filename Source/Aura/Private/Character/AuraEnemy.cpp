// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

void AAuraEnemy::HighlightActor()
{
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Blue, FString(TEXT("Highlight")));
}

void AAuraEnemy::UnHighlightActor()
{
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, FString(TEXT("UnHighlight")));
}
