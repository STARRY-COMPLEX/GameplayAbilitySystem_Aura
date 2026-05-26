// Copyright Lie

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class AAuraAIController;
class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	virtual void PossessedBy(AController* NewController) override;
	
	/** Enemy Interface */
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	/** end Enemy Interface */
	
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget);
	virtual AActor* GetCombatTarget_Implementation() const;
	/** end Combat Interface */
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	UPROPERTY(BlueprintReadOnly, Category = "Custom Property | Combat")
	bool bHitReacting = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Custom Property | Combat")
	float LifeSpan = 5.f;
	
	UPROPERTY(BlueprintReadWrite, Category = "Custom Property | Combat")
	TObjectPtr<AActor> CombatTarget;
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Character Class Defaults")
	int32 Level = 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	UPROPERTY(EditAnywhere, Category = "Custom Property | AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
};
