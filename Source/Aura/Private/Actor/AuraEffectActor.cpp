// Copyright Lie


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor(){
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay(){
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplayEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass){
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;
	
	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && (InfiniteRemovalPolicy == EEffectRemovalPolicy::EERP_RemoveOnEndOverlap)){
		ActiveEffectHandles.Add(TargetASC, ActiveEffectHandle);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor){
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::EEAP_ApplyOnOverlap){
		ApplayEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationApplicationPolicy == EEffectApplicationPolicy::EEAP_ApplyOnOverlap){
		ApplayEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::EEAP_ApplyOnOverlap){
		ApplayEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor){
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::EEAP_ApplyOnEndOverlap){
		ApplayEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationApplicationPolicy == EEffectApplicationPolicy::EEAP_ApplyOnEndOverlap){
		ApplayEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::EEAP_ApplyOnEndOverlap){
		ApplayEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteRemovalPolicy == EEffectRemovalPolicy::EERP_RemoveOnEndOverlap){
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;
		if (ActiveEffectHandles.Contains(TargetASC)){
			TargetASC->RemoveActiveGameplayEffect(ActiveEffectHandles[TargetASC], 1);
			ActiveEffectHandles.Remove(TargetASC);
		}
	}
}


