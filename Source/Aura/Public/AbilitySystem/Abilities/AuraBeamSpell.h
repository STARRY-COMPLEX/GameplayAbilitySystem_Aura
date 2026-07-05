// Copyright Lie

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraBeamSpell.generated.h"

UCLASS()
class AURA_API UAuraBeamSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void StoreMouseDataInfo(const FHitResult& HitResult);
	
	UFUNCTION(BlueprintCallable)
	void StoreOwnerVariables();
	
	UFUNCTION(BlueprintCallable)
	void TraceFirstTarget(const FVector& BeamTargetLocation);
	
	UFUNCTION(BlueprintCallable)
	void StoreAdditionTargets(TArray<AActor*>& OutAdditionalTargets);
	
	UFUNCTION(BlueprintImplementableEvent)
	void PrimaryTargetDied(AActor* DeadActor);
	
	UFUNCTION(BlueprintImplementableEvent)
	void AdditionalTargetDied(AActor* DeadActor);
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Custom Property | Beam")
	FVector MouseHitLocation;
	
	UPROPERTY(BlueprintReadWrite, Category = "Custom Property | Beam")
	TObjectPtr<AActor> MouseHitActor;
	
	UPROPERTY(BlueprintReadWrite, Category = "Custom Property | Beam")
	TObjectPtr<APlayerController> OwnerPlayerController;
	
	UPROPERTY(BlueprintReadWrite, Category = "Custom Property | Beam")
	TObjectPtr<ACharacter> OwnerCharacter;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Beam")
	int32 MaxNumShockTargets = 5;
	
};
