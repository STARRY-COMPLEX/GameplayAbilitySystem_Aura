// Copyright Lie


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility){
	UTargetDataUnderMouse* Myobj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return Myobj;
}

void UTargetDataUnderMouse::Activate(){
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	
	FHitResult CursorHit;
	
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	ValidData.Broadcast(CursorHit.ImpactPoint);
}
