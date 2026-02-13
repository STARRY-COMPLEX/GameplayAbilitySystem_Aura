// Copyright Lie

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UENUM()
enum class EEffectApplicationPolicy{
	EEAP_ApplyOnOverlap UMETA(DisplayName = "ApplyOnOverlap"),
	EEAP_ApplyOnEndOverlap UMETA(DisplayName = "ApplyOnEndOverlap"),
	EEAP_DoNotApply UMETA(DisplayName = "DoNotApply")
};

UENUM()
enum class EEffectRemovalPolicy{
	EERP_RemoveOnEndOverlap UMETA(DisplayName = "RemoveOnEndOverlap"),
	EERP_DoNotRemove UMETA(DisplayName = "DoNotRemove")
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplayEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Applied Effects")
	bool bDestroyOnEffectRemoval = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Applied Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::EEAP_DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Applied Effects")
	EEffectApplicationPolicy DurationApplicationPolicy = EEffectApplicationPolicy::EEAP_DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Applied Effects")
	EEffectApplicationPolicy InfiniteApplicationPolicy = EEffectApplicationPolicy::EEAP_DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Applied Effects")
	EEffectRemovalPolicy InfiniteRemovalPolicy = EEffectRemovalPolicy::EERP_RemoveOnEndOverlap;

	TMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveEffectHandles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Applied Effects")
	float ActorLevel = 1.f;
};
