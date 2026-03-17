// Copyright Lie


#include "AuraAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get(){
	check(GEngine)
	
	UAuraAssetManager* AuraAssetManage = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManage;
}

void UAuraAssetManager::StartInitialLoading(){
	Super::StartInitialLoading();
	FAuraGameplayTags::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
