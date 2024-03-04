// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraBilitySystemLibrary.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenentration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);

	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenentration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistence, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);

	}

};

static const AuraDamageStatics& DamageStatic()
{
	// static 변수는 함수가 종료되도 사라지지 않고 오로지 1개만 존재한다
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatic().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatic().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatic().ArmorPenentrationDef);
	RelevantAttributesToCapture.Add(DamageStatic().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatic().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatic().CriticalHitResistenceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvator = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAcator = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvator);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAcator);


	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();


	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set bu caller magnitute
	float Damage = 0.f;
	for (auto& Pair : FAuraGamplayTags::Get().DamageTypesToResistances)
	{
		const float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key);

		Damage += DamageTypeValue;
	}

	// Caputure BlockCHance on Target, and determine if ther was a successful block

	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().BlockChanceDef, EvaluationParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max(0.f, TargetBlockChance);

	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	UAuraBilitySystemLibrary::SetIsBlockHit(EffectContextHandle, bBlocked);


	// if block, halve the damage
	if (bBlocked)
	{
		Damage = Damage / 2.f;
	}

	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().ArmorDef, EvaluationParameters, TargetArmor);
	TargetArmor = FMath::Max(0.f, TargetArmor);

	float SourceArmorPenentration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().ArmorPenentrationDef, EvaluationParameters, SourceArmorPenentration);
	SourceArmorPenentration = FMath::Max(0.f, SourceArmorPenentration);

	UCharacterClassInfo* CharacterInfo = UAuraBilitySystemLibrary::GetCharacterClassInfo(SourceAvator);

	FRealCurve* ArmorPenentrationCurve = CharacterInfo->DamageCalculationCoefficient->FindCurve(FName("ArmorPenentration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenentrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());

	// Armor Penentration ignores a percentage of the target's armor
	const float EffectiveArmor = (TargetArmor *= (100 - SourceArmorPenentration * ArmorPenetrationCoefficient) / 100.f);


	FRealCurve* EffectiveArmorCurve = CharacterInfo->DamageCalculationCoefficient->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCurveCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());

	Damage *= (100 - EffectiveArmor * EffectiveArmorCurveCoefficient) / 100.f;



	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().CriticalHitChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max(0.f, SourceCriticalHitChance);

	float TargetCriticalHitResistence = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().CriticalHitResistenceDef, EvaluationParameters, TargetCriticalHitResistence);
	TargetCriticalHitResistence = FMath::Max(0.f, TargetCriticalHitResistence);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatic().CriticalHitDamageDef, EvaluationParameters, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max(0.f, SourceCriticalHitDamage);


	FRealCurve* CriticalHitResistenceCurve = CharacterInfo->DamageCalculationCoefficient->FindCurve(FName("CriticalHitResistence"), FString());
	const float CriticalHitResistenceCoefficient = CriticalHitResistenceCurve->Eval(TargetCombatInterface->GetPlayerLevel());


	// Critical hit resistacne reduces ciritcla hit chance by a certain percentage
	const float EffectiveCiriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistence * CriticalHitResistenceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCiriticalHitChance;

	Damage = bCriticalHit ? 2.f * bCriticalHit + SourceCriticalHitDamage : Damage;

	UAuraBilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);

	const FGameplayModifierEvaluatedData EvaluateData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluateData);
}
