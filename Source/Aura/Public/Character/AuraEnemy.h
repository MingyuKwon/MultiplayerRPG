// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/EnemyInterface.h"
#include "Character/AuraCharacterBase.h"
#include "AuraEnemy.generated.h"

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
public:
	AAuraEnemy();

	// - start - EnemyInterface 
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// - end - EnemyInterface 

	// - start - Combatnterface 
	virtual int32 GetPlayerLevel();
	// - end - Combatnterface 


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character class Defaults")
	int32 Level = 1;

private:
	
};
