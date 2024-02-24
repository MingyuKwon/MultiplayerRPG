// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponentBase.h"
#include "AbilitySystem/Ability/AuraGameplayAbilityBase.h"


void UAuraAbilitySystemComponentBase::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponentBase::ClientEffectApplied);
}

void UAuraAbilitySystemComponentBase::AddCharacterAbilites(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		if (UAuraGameplayAbilityBase* auraAbility = Cast<UAuraGameplayAbilityBase>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(auraAbility->StartupInputTag);
		}

		GiveAbility(AbilitySpec);
	}
}

void UAuraAbilitySystemComponentBase::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& Abilities : GetActivatableAbilities())
	{
		if (Abilities.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(Abilities);
			if (!Abilities.IsActive())
			{
				TryActivateAbility(Abilities.Handle);
			}
		}
	}
	
}

void UAuraAbilitySystemComponentBase::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& Abilities : GetActivatableAbilities())
	{
		if (Abilities.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(Abilities);
		}
	}

}

void UAuraAbilitySystemComponentBase::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTagsDelegates.Broadcast(TagContainer);

	
}
