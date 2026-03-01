// Copyright Lie

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraMenuWidgetController.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UAuraMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependences() override;
	
	UPROPERTY(BlueprintAssignable, Category = "Custom Property | GAS | Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | AttributeInfo")
	TObjectPtr<UAttributeInfo> AttributeInfo;
};
