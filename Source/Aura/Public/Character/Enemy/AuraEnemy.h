// Copyright Lie

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	
	/** Enemy Interface */
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	/** end Enemy Interface */
	
	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	UPROPERTY(BlueprintReadOnly, Category = "Custom Property | Combat")
	bool bHitReacting = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Custom Property | Combat")
	float BaseWalkSpeed = 250.f;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Character Class Defaults")
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom Property | Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::ECC_Warrior;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
};
