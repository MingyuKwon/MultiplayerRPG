// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGamplayTags FAuraGamplayTags::GameplayTags;

void FAuraGamplayTags::InitializeNativeGameplayTags()
{
	// Primary Attribute
	GameplayTags.Attribute_Primary_Strength =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Strength"),
			FString("Increases physical damage"));

	GameplayTags.Attribute_Primary_Inteligence =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Inteligence"),
			FString("Increases Magical damage"));

	GameplayTags.Attribute_Primary_Resilience =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Resilience"),
			FString("Increases Armor and Armor penentration"));

	GameplayTags.Attribute_Primary_Vigor =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Vigor"),
			FString("Increases Health"));


	// Secondary Attribute
	GameplayTags.Attribute_Secondary_Armor =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.Armor"), 
			FString("Reduces damage taken, improves Block Chance"));

	GameplayTags.Attribute_Secondary_ArmorPenetration =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.ArmorPenetration"),
			FString("Ignore Percentage of enemy Armor, increases Critical Hit Chance"));

	GameplayTags.Attribute_Secondary_BlockChance =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.BlockChance"),
			FString("Chance to cut incoming damage in half"));

	GameplayTags.Attribute_Secondary_CriticalHitChance =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.CriticalHitChance"),
			FString("Chance to double damage plus ciritical hit bonus"));

	GameplayTags.Attribute_Secondary_CriticalHitDamage =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.CriticalHitDamage"),
			FString("Bonus damage added when a critical hit is scored"));

	GameplayTags.Attribute_Secondary_CriticalHitResistance =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.CriticalHitResistance"),
			FString("Reduces Critical Hit Chance of attacking enemies"));

	GameplayTags.Attribute_Secondary_HealthRegeneration =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.HealthRegeneration"),
			FString("Amount of Health regenerated every 1 second"));

	GameplayTags.Attribute_Secondary_ManaRegeneration =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.ManaRegeneration"),
			FString("Amount of Mana regenerated every 1 second"));

	GameplayTags.Attribute_Secondary_MaxHealth =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.MaxHealth"),
			FString("Maximum amount of Health obtainable"));

	GameplayTags.Attribute_Secondary_MaxMana =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.MaxMana"),
			FString("Maximum amount of Mana obtainable"));



	// Input Attribute
	GameplayTags.InputTag_LMB =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.LMB"),
			FString("Input Tag for Left Mouse Button"));

	GameplayTags.InputTag_RMB =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.RMB"),
			FString("Input Tag for Rigft Mouse Button"));

	GameplayTags.InputTag_1 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.1"),
			FString("Input Tag for 1 Button"));

	GameplayTags.InputTag_2 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.2"),
			FString("Input Tag for 2 Button"));

	GameplayTags.InputTag_3 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.3"),
			FString("Input Tag for 3 Button"));

	GameplayTags.InputTag_4 =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("InputTag.4"),
			FString("Input Tag for 4 Button"));


	// Damage Types

	GameplayTags.Damage =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage"),
			FString("Damage"));

	GameplayTags.Damage_Fire =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Fire"),
			FString("Fire Damage Type"));

	GameplayTags.Damage_Lightning =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Lightning"),
			FString("Lightning Damage Type"));

	GameplayTags.Damage_Arcane =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Arcane"),
			FString("Arcane Damage Type"));

	GameplayTags.Damage_Physical =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Damage.Physical"),
			FString("Physical Damage Type"));

	// Resistances

	GameplayTags.Attribute_Resistance_Fire =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Resistance.Fire"),
			FString("Resistance to Fire"));

	GameplayTags.Attribute_Resistance_Lightning =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Resistance.Lightning"),
			FString("Resistance to Lightning"));

	GameplayTags.Attribute_Resistance_Arcane =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Resistance.Arcane"),
			FString("Resistance to Arcane"));

	GameplayTags.Attribute_Resistance_Physical =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Resistance.Physical"),
			FString("Resistance to Physical"));

	// map of Damage Types to Resistances

	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attribute_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attribute_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attribute_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attribute_Resistance_Physical);


	//Effect

	GameplayTags.Effects_HitReact =
		UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Effects.HitReact"),
			FString("Tag granted when Hit Reacting"));
}
