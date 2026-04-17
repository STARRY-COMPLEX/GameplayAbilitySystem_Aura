// Copyright Lie

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraDamageGameplayAbility.generated.h"

UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Custom Property | Projectile")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Dagage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
