// Copyright Lie


#include "UI/WidgetController/AuraMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAuraMenuWidgetController::BroadcastInitialValues(){
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	check(AttributeInfo);

	for (TPair<FGameplayTag, FGameplayAttribute(*)()>& Pair : AS->TagsToAttributes){
		BroadcastAttributeInfo(Pair.Key, Pair.Value());	
	}
}

void UAuraMenuWidgetController::BindCallbacksToDependences(){
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	for (TPair<FGameplayTag, FGameplayAttribute(*)()>& Pair : AS->TagsToAttributes){
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data){
				BroadcastAttributeInfo(Pair.Key, Pair.Value());	
			}
		);
	}
	
}

void UAuraMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
