// Copyright Lie

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8{
	ECC_Elementalist UMETA(DisplayName = "Elementalist"),
	ECC_Warrior UMETA(DisplayName = "Warrior"),
	ECC_Ranger UMETA(DisplayName = "Range")
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	
	
};

UCLASS()
class AURA_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Character Class Defaults")
	TMap<ECharacterClass,FCharacterClassDefaultInfo> CharacterClassInformation;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Property | Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;
	
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);
};
