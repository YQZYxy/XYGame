// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "LogicConfig.generated.h"


#define CONFIG_INIT_FILE(func) \
if (!func(path, err))\
{\
	return false; \
}\

#define CONFIG_FILE_NAME(in_path)  *( path.ToString() + TEXT(in_path) + TEXT('.')+ TEXT(in_path)  + TEXT('\'') )

#define GET_CONFIG_ROWNAMES(file_name, str_name, arr_name)\
UDataTable* DataTable = LoadObject<UDataTable>(NULL, CONFIG_FILE_NAME(file_name));\
if (!DataTable)\
{\
	err += __FUNCTION__;\
	err += "  ";\
	err += FString::FromInt(__LINE__);\
	err += "  ";\
	err += CONFIG_FILE_NAME(file_name);\
	return false;\
}\
FString str_name;\
TArray<FName> RowNames;\
arr_name = DataTable->GetRowNames();\

#define CONFIG_ERROR(info_str)	err += __FUNCTION__;err +=" " ; err += FString::FromInt(__LINE__);err +=" ";err +=info_str;\
	

UCLASS()
class YQZY_API ULogicConfig : public UObject
{
	GENERATED_BODY()
public:
	virtual bool Init(const FName& path, FString& err) { return true; }
};
