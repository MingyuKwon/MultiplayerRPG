// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Mesh")));
	RootComponent = Mesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Sphere")));
	Sphere->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);

	// TODO:: CHange this to apply a Gamplay Effect, for now using concst_cast as a hack
	if (ASCInterface)
	{
		// 여기서 GetAttributeSet이 반환은 const로 해서 const로 밖에 못받음
		const UAuraAttributeSet* AuraAttributeSet =  
			Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
	
		UE_LOG(LogTemp, Warning, TEXT("HP healed"));
		Destroy();
		//AuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


