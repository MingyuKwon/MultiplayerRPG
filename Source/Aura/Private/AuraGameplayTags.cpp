// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGamplayTags FAuraGamplayTags::GameplayTags;

void FAuraGamplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attribute_Secondary_Armor =
		UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves Block Chance"));



}
