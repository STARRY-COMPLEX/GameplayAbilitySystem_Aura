// Copyright Lie


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "UI/Widget/DamageTextComponent.h"

AAuraPlayerController::AAuraPlayerController(){
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::PlayerTick(float DeltaTime){
	Super::PlayerTick(DeltaTime);
	CurserTrace();
	AutoRun();
}

void AAuraPlayerController::ShowDamageNamber_Implementation(float DamageAmount, ACharacter* TargetCharacter, bool bBlockHit, bool bCriticalHit){
	if (IsValid(TargetCharacter) && DamageTextComponentClass){
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bBlockHit, bCriticalHit);
	}
}

void AAuraPlayerController::AutoRun(){
	if (!bAutoRunning) return;
	if(APawn* ControlledPawn = GetPawn<APawn>()){
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction, 1.f);
		
		const float DistanceToDestination = (LocationOnSpline - CashedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius){
			bAutoRunning = false;
		}
	}
}

void AAuraPlayerController::CurserTrace(){
	GetHitResultUnderCursor(ECC_Visibility, false, CurserHit);
	if (!CurserHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CurserHit.GetActor());
	
	if (LastActor != ThisActor){
		if (LastActor) LastActor->UnHighLightActor();
		if (ThisActor) ThisActor->HighLightActor();
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
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)){
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag){
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)){
		if (GetASC()) GetASC()->AbilityInputTagRelease(InputTag);
		return;
	}
	
	if (GetASC()) GetASC()->AbilityInputTagRelease(InputTag);
	
	if (!bTargeting && !bShiftKeyDown){
		const APawn* ControlledPawn = GetPawn<APawn>();
		
		if (ControlledPawn && (FollowTime <= ShortPressThreshold)){
			if(UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CashedDestination)){
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints){
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				}
				if (NavPath->PathPoints.Num() > 0){
					CashedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
					bAutoRunning = true;
				}
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHold(FGameplayTag InputTag){
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)){
		if (GetASC()) GetASC()->AbilityInputTagHold(InputTag);
		return;
	}
	
	if (bTargeting || bShiftKeyDown){
		if (GetASC()) GetASC()->AbilityInputTagHold(InputTag);
	}else{
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		if (CurserHit.bBlockingHit) CashedDestination = CurserHit.ImpactPoint;
		
		if (APawn* ControlledPawn = GetPawn<APawn>()){
			const FVector WorldDirection = (CashedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
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
	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftPressed);
	AuraInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftReleased);
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

