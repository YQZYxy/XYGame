// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYContextEffectsLibraryFactory.h"

#include "Feedback/ContextEffects/YQZYContextEffectsLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYContextEffectsLibraryFactory)

class FFeedbackContext;
class UClass;
class UObject;

UYQZYContextEffectsLibraryFactory::UYQZYContextEffectsLibraryFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UYQZYContextEffectsLibrary::StaticClass();

	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
}

UObject* UYQZYContextEffectsLibraryFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UYQZYContextEffectsLibrary* YQZYContextEffectsLibrary = NewObject<UYQZYContextEffectsLibrary>(InParent, Name, Flags);

	return YQZYContextEffectsLibrary;
}
