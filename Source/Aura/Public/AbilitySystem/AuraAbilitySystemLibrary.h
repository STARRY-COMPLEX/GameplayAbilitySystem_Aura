// Copyright Lie

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

struct FDamageEffectParams;
struct FGameplayEffectContextHandle;
class UAbilityInfo;
class AAuraHUD;
struct FWidgetControllerParams;
class USpellMenuWidgetController;
class UAuraMenuWidgetController;
class UOverlayWidgetController;
class UAbilitySystemComponent;

UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | Widget Controller")
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AAuraHUD*& OutAuraHUD);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | Widget Controller", meta = (DefaultToSelf = "WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | Widget Controller", meta = (DefaultToSelf = "WorldContextObject"))
	static UAuraMenuWidgetController* GetAuraMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | Widget Controller", meta = (DefaultToSelf = "WorldContextObject"))
	static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | CharacterClassDefaults")
	static UAbilityInfo* GetAbilityInfo(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static bool IsBlockHit(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static FVector GetKnockForce(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static void SetIsBlockHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockHit);

	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsSuccessful);

	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDamage);

	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDuration);

	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffFrequency);
	
	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType);
	
	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpulse);
	
	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayEffects")
	static void SetKnockForce(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce);
	
	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayMechanics")
	static void GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin);

	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayMechanics")
	static void GetClosestTargets(int32 MaxTarget, const TArray<AActor*>& Actors, TArray<AActor*>& OutClosestActors, const FVector& Origin);
	
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayMechanics")
	static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);
	
	UFUNCTION(BlueprintCallable, Category = "Custom Property | AuraAbilitySystemLibrary | DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayMechanics")
	static TArray<FRotator> EvenlySpaceRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators);
	
	UFUNCTION(BlueprintPure, Category = "Custom Property | AuraAbilitySystemLibrary | GameplayMechanics")
	static TArray<FVector> EvenlyRotateVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors);
	
	static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel);
};
