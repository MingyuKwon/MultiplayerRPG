// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGamplayTags
 * 
 * SingleTon containing native Gameplay Tags
 */


struct FAuraGamplayTags
{
public:
	static const FAuraGamplayTags& Get() {return GameplayTags;}
	static void InitializeNativeGameplayTags();

	FGameplayTag Attribute_Secondary_Armor;
protected:

private:
	static FAuraGamplayTags GameplayTags;
};