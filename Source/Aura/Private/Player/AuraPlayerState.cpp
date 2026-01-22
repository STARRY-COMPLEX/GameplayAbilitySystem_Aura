// Copyright Lie


#include "Player/AuraPlayerState.h"
#include "AbilitySystemComponent.h"

AAuraPlayerState::AAuraPlayerState(){
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	
	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100;
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const{
	return AbilitySystemComponent;
}
