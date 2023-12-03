// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYCosmeticCheats.h"
#include "Cosmetics/YQZYCharacterPartTypes.h"
#include "YQZYControllerComponent_CharacterParts.h"
#include "GameFramework/CheatManagerDefines.h"
#include "System/YQZYDevelopmentStatics.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYCosmeticCheats)

//////////////////////////////////////////////////////////////////////
// UYQZYCosmeticCheats

UYQZYCosmeticCheats::UYQZYCosmeticCheats()
{
#if UE_WITH_CHEAT_MANAGER
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		UCheatManager::RegisterForOnCheatManagerCreated(FOnCheatManagerCreated::FDelegate::CreateLambda(
			[](UCheatManager* CheatManager)
			{
				CheatManager->AddCheatManagerExtension(NewObject<ThisClass>(CheatManager));
			}));
	}
#endif
}

void UYQZYCosmeticCheats::AddCharacterPart(const FString& AssetName, bool bSuppressNaturalParts)
{
#if UE_WITH_CHEAT_MANAGER
	if (UYQZYControllerComponent_CharacterParts* CosmeticComponent = GetCosmeticComponent())
	{
		TSubclassOf<AActor> PartClass = UYQZYDevelopmentStatics::FindClassByShortName<AActor>(AssetName);
		if (PartClass != nullptr)
		{
			FYQZYCharacterPart Part;
			Part.PartClass = PartClass;

			CosmeticComponent->AddCheatPart(Part, bSuppressNaturalParts);
		}
	}
#endif	
}

void UYQZYCosmeticCheats::ReplaceCharacterPart(const FString& AssetName, bool bSuppressNaturalParts)
{
	ClearCharacterPartOverrides();
	AddCharacterPart(AssetName, bSuppressNaturalParts);
}

void UYQZYCosmeticCheats::ClearCharacterPartOverrides()
{
#if UE_WITH_CHEAT_MANAGER
	if (UYQZYControllerComponent_CharacterParts* CosmeticComponent = GetCosmeticComponent())
	{
		CosmeticComponent->ClearCheatParts();
	}
#endif	
}

UYQZYControllerComponent_CharacterParts* UYQZYCosmeticCheats::GetCosmeticComponent() const
{
	if (APlayerController* PC = GetPlayerController())
	{
		return PC->FindComponentByClass<UYQZYControllerComponent_CharacterParts>();
	}

	return nullptr;
}

