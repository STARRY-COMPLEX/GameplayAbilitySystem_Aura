// Copyright Lie


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor){
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1);
	for (TPair<FGameplayTag, FScalableFloat> Pair : DamageTypes){
		float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaledDamage);
	}
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
	
}

FTagMontage UAuraDamageGameplayAbility::GetRandomTagMontageFromArray(const TArray<FTagMontage>& TagMontageArray) const{
	if (TagMontageArray.Num() > 0){
		const int32 Selection = FMath::RandRange(0, TagMontageArray.Num() - 1);
		return TagMontageArray[Selection];
	}

	return FTagMontage();
}

float UAuraDamageGameplayAbility::GetDamageByDamageType(float InLevel, const FGameplayTag& DamageType) const{
	checkf(DamageTypes.Contains(DamageType), TEXT("GameplayAbility [%s] does not contain DamageType [%s]"), *GetNameSafe(this), *DamageType.ToString());
	return DamageTypes[DamageType].GetValueAtLevel(InLevel);
}
