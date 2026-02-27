// Copyright Lie


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFind) const{
	for (const FAuraAttributeInfo& Info : AttributeInformation){
		if (Info.AttributeTag == AttributeTag){
			return Info;
		}
	}
	
	if (bLogNotFind){
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
