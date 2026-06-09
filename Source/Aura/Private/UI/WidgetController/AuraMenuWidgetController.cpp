// Copyright Lie


#include "UI/WidgetController/AuraMenuWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/AuraPlayerState.h"

void UAuraMenuWidgetController::BroadcastInitialValues(){
	check(AttributeInfo);

	for (TPair<FGameplayTag, FGameplayAttribute(*)()>& Pair : GetAuraAS()->TagsToAttributes){
		BroadcastAttributeInfo(Pair.Key, Pair.Value());	
	}
	
	AttributePointChangedDelegate.Broadcast(GetAuraPS()->GetAttributePoints());
	SpellPointChangedDelegate.Broadcast(GetAuraPS()->GetSpellPoints());
}

void UAuraMenuWidgetController::BindCallbacksToDependences(){
	check(AttributeInfo);
	for (TPair<FGameplayTag, FGameplayAttribute(*)()>& Pair : GetAuraAS()->TagsToAttributes){
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data){
				BroadcastAttributeInfo(Pair.Key, Pair.Value());	
			}
		);
	}
	
	GetAuraPS()->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 Points){
			AttributePointChangedDelegate.Broadcast(Points);
		}	
	);
	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 Points){
			SpellPointChangedDelegate.Broadcast(Points);
		}	
	);
}

void UAuraMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag){
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	
	AuraASC->UpgradeAttribute(AttributeTag);
}

void UAuraMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
                                                       const FGameplayAttribute& Attribute) const{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
