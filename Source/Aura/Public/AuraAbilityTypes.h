#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext{
	GENERATED_BODY()
	
public:
	bool IsCriticalHit() const {return bIsCriticalHit;}
	bool IsBlockHit() const {return bIsBlockHit;}
	
	void SetIsCriticalHit(const bool bInIsCriticalHit){bIsCriticalHit = bInIsCriticalHit;}
	void SetIsBlockHit(const bool bInIsBlockHit){bIsBlockHit = bInIsBlockHit;}
	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}
	
	virtual FAuraGameplayEffectContext* Duplicate() const override
	{
		FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
	
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
protected:
	UPROPERTY()
	bool bIsBlockHit = false;
	
	UPROPERTY()
	bool bIsCriticalHit = false;
};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>{
	enum{
		WithNetSerializer = true,
		WithCopy = true 
	};
};