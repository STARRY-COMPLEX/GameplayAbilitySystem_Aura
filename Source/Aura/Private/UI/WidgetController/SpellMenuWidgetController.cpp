// Copyright Lie


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues(){
	BroadcastAbilityInfo();
	SpellPointsChanged.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependences(){
	GetAuraASC()->AbilitiesStatusChanged.AddLambda(
		[this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag){
			if (AbilityInfo){
				FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
				Info.StatusTag = StatusTag;
				AbilityInfoDelegate.Broadcast(Info);
			}
		}	
	);
	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 SpellPoints){
			SpellPointsChanged.Broadcast(SpellPoints);
		}
	);
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag){
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	const int32 SpellPoints = GetAuraPS()->GetSpellPoints();
	FGameplayTag AbilityStatus;
	
	const bool bTagValid = AbilityTag.IsValid();
	const bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	const FGameplayAbilitySpec* AbilitySpec = GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);
	const bool bSpecValid = AbilitySpec != nullptr;

	if (!bTagValid || bTagNone || !bSpecValid){
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}else{
		AbilityStatus = GetAuraASC()->GetStatusFromSpec(*AbilitySpec);
	}
	
	bool bEnableSpellPoints = false;
	bool bEnableEquip = false;
	ShouldEnableButtons(AbilityStatus, SpellPoints, bEnableSpellPoints, bEnableEquip);
	
	SpellGlobeSelectedDelegate.Broadcast(bEnableSpellPoints, bEnableEquip);
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints,
	bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButtons){
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	
	bShouldEnableSpellPointsButton = false;
	bShouldEnableEquipButtons = false;
	if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped)){
		bShouldEnableEquipButtons = true;
		if (SpellPoints > 0) bShouldEnableSpellPointsButton = true;
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible)){
		if (SpellPoints > 0) bShouldEnableSpellPointsButton = true;
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked)){
		bShouldEnableEquipButtons = true;
		if (SpellPoints > 0) bShouldEnableSpellPointsButton = true;
	}
}
