// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraOverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature, float, NewFloat);

/**
 * 
 */
class UAuraUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);


UCLASS(Blueprintable, BlueprintType)
class AURA_API UAuraOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	virtual void AssetTagBroadCasted(const FGameplayTagContainer& GameplayTagContainer);
	// ���� �帧�� ���� 
	// 1. ���� �Ӽ��� ����
	// 2. controller�� �Ӽ��� ���� �� ���� delegate�� �޾Ƽ� �˾�����
	// 3. widget�� controller���� ���� ���� �� ���� delegate�� �޾Ƽ� �˾�����
	// ���Ӽ��� �Ӽ� <= controller <= widget �̷��� �Ǿ��ֱ⿡ �̺�Ʈ �޴� ���� 2�� �ؾ� ��μ� 
	// �Ӽ��� �ٲ� ������ ������ ���ϰ� �ϴ� �۾��� �Ϸ� �ȴ�

	// Begin  ������ ��Ʈ�ѷ��� ����� signature
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangeSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Message")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;
	// End  ������ ��Ʈ�ѷ��� ����� signature

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

};

template<typename T>
inline T* UAuraOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
