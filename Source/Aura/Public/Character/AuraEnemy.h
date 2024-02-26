// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"
#include "Interaction/EnemyInterface.h"
#include "Aura/Aura.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacterBase.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
/**
 * 
 */

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character class Defaults")
	int32 Level = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Elementalist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	TObjectPtr<UWidgetComponent> HealthBar;

public:
	AAuraEnemy();

	// - start - EnemyInterface 
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// - end - EnemyInterface 

	// - start - Combatnterface 
	virtual int32 GetPlayerLevel();
	// - end - Combatnterface 

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxHealthChanged;




private:
	
};
