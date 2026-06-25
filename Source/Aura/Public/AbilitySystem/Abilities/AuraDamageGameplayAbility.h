// Copyright Lie

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraDamageGameplayAbility.generated.h"

struct FTagMontage;

UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
	
	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr) const;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Custom Property | Projectile")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Damage")
	FGameplayTag DamageType;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Damage")
	FScalableFloat Damage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Damage")
	float DebuffChance = 20.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Damage")
	float DebuffDamage = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Damage")
	float DebuffFrequency = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Damage")
	float DebuffDuration = 3.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Damage")
	float DeathImpulseMagnitude = 1000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Damage")
	float KnockbackForceMagnitude = 1000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Damage")
	float KnockbackChance = 0.f;
	
	UFUNCTION(BlueprintPure)
	FTagMontage GetRandomTagMontageFromArray(const TArray<FTagMontage>& TagMontageArray) const;
};
