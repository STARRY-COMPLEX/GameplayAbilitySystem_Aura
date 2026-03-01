// Copyright Lie


#include "UI/WidgetController/AuraMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

void UAuraMenuWidgetController::BroadcastInitialValues(){
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	check(AttributeInfo);

	for (TPair<FGameplayTag, FGameplayAttribute(*)()>& Pair : AS->TagsToAttributes){
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);		
	}
}

void UAuraMenuWidgetController::BindCallbacksToDependences(){
	
}
