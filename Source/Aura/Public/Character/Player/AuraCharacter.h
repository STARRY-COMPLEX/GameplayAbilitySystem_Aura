// Copyright Lie

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();
	
protected:
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> ViewCamera;
};
