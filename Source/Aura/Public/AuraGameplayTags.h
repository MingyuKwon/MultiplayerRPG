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

	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Inteligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Vigor;


	FGameplayTag Attribute_Secondary_MaxHealth;
	FGameplayTag Attribute_Secondary_MaxMana;
	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_ArmorPenetration;
	FGameplayTag Attribute_Secondary_BlockChance;
	FGameplayTag Attribute_Secondary_CriticalHitChance;
	FGameplayTag Attribute_Secondary_CriticalHitDamage;
	FGameplayTag Attribute_Secondary_CriticalHitResistance;
	FGameplayTag Attribute_Secondary_HealthRegeneration;
	FGameplayTag Attribute_Secondary_ManaRegeneration;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;


	FGameplayTag Damage;
	FGameplayTag Damage_Fire;

	TArray<FGameplayTag> DamageTypes;

	FGameplayTag Effects_HitReact;

protected:

private:
	static FAuraGamplayTags GameplayTags;
};