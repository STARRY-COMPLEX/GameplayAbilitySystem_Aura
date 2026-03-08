// Copyright Lie


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController(){
	bReplicates = true;
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime){
	Super::PlayerTick(DeltaTime);
	
	CurserTrace();
}

void AAuraPlayerController::CurserTrace(){
	FHitResult CurserHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CurserHit);
	if (!CurserHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CurserHit.GetActor());
	
	/**
	 *  Line trace from curser. There are several Scenarias:
	 *  A. LastActor is null && This Actor is null
	 *		- Do nothing
	 *	B. LastActor is null && This Actor is Valid
	 *		- HighLight ThisActor
	 *	C. LastActor is Valid && This Actor is null
	 *		- UnHighLight LastActor
	 *	D. Both actors are valid, but LastActor != ThisActor
	 *		- UnHighLight LastActor && HighLight ThisActor
	 *	E. Both actors are valid, and are the same actor
	 *		- Do nothing
	 */
	if (LastActor == nullptr){
		if (ThisActor != nullptr){
			// Case B
			ThisActor->HighLightActor();
		}else{
			// Case A - both are null, do nothing
		}
	}else{ // LastActor is valid
		if (ThisActor == nullptr){
			// Case C
			LastActor->UnHighLightActor();
		}
		else{ // both actor is valid
			if (LastActor != ThisActor){
				// Case D
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}else{
				// Case E - do nothing
			}
		}
	}
}

void AAuraPlayerController::BeginPlay(){
	Super::BeginPlay();
	check(AuraContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem){
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag){
	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag){
	if (GetASC() == nullptr) return;
	
	GetASC()->AbilityInputTagRelease(InputTag);
}

void AAuraPlayerController::AbilityInputTagHold(FGameplayTag InputTag){
	if (GetASC() == nullptr) return;
	
	GetASC()->AbilityInputTagHold(InputTag);
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC(){
	if (AuraAbilitySystemComponent == nullptr){
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::SetupInputComponent(){
	Super::SetupInputComponent();
	
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig, this, &AAuraPlayerController::AbilityInputTagPressed, &AAuraPlayerController::AbilityInputTagReleased, &AAuraPlayerController::AbilityInputTagHold);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue){
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControlledPawn = GetPawn<APawn>()){
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

