#pragma once

#include "CoreMinimal.h"
#include "Game/Config/LogicConfig.h"
#include "LogicConfigManager.generated.h"

USTRUCT(BlueprintType)
struct FLogicConfigManagerData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable FString")
		FName class_type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable FString")
		FName path;
};

#define NEW_CONFIG(class_type)										\
{																	\
	if(m_class_config_map.Contains(#class_type))					\
	{																\
		LogFatal(#class_type);										\
	}																\
	m_class_config_map.Add(#class_type, NewObject<class_type>());	\
}

#define GET_CONFIG(class_type)									\
	UFUNCTION(BlueprintCallable, Category = "")					\
	class_type* Get##class_type() const 						\
{																\
	auto ptr = m_class_config_map.Find(#class_type);			\
	if (!ptr)return nullptr; 									\
	return (class_type*)*ptr;									\
}

//#define GET_CONFIG(class_type)\
//	UFUNCTION(BlueprintCallable, Category = "")\
//	class_type* Get##class_type() const{return (class_type*)class_config_map[#class_type];}

class ULogicConfig;
class UWeaponConfig;
class UTaskConfig;


#define LCMCFG ULogicConfigManager::GetLogicConfigManagerInstance()

UCLASS(Config = Game)
class YQZY_API ULogicConfigManager : public UObject
{
	GENERATED_BODY()
public:
	ULogicConfigManager();//在构造里面添加 NEW_CONFIG 对应类型
	
	GET_CONFIG(UWeaponConfig);
	GET_CONFIG(UTaskConfig);

public:
	UFUNCTION(BlueprintCallable, Category = "AYQZY_LogicConfigManager")
	bool Init();

	UFUNCTION(BlueprintCallable, Category = "LogicConfigManager")
	static bool OnReload();

	UFUNCTION(BlueprintCallable, Category = "LogicConfigManager")
	static ULogicConfigManager* GetLogicConfigManagerInstance();
	UFUNCTION(BlueprintCallable, Category = "LogicConfigManager")
	static void DeleteUObject();

	UFUNCTION(BlueprintCallable, Category = "LogicConfigManager")
		ULogicConfig* GetConfigByName(FName class_name);

private:
	bool InitPath();

	UPROPERTY()
	TMap<FName, FName> m_data_path_map;
	UPROPERTY()
	TMap<FName, ULogicConfig*> m_class_config_map;

public:
	
	//动态读取DataTable数据表格......
	UFUNCTION(BlueprintCallable, DisplayName = "Fill Data Table from CSV String", Category = "DataTable")
		static bool FillDataTableFromCSVString(UDataTable* DataTable, const FString& CSVString);

	UFUNCTION(BlueprintCallable, DisplayName = "Fill Data Table from CSV File", Category = "DataTable")
		static bool FillDataTableFromCSVFile(UDataTable* DataTable, const FString& CSVFilePath);

	UFUNCTION(BlueprintCallable, DisplayName = "Fill Data Table from JSON String", Category = "DataTable")
		static bool FillDataTableFromJSONString(UDataTable* DataTable, const FString& JSONString);

	UFUNCTION(BlueprintCallable, DisplayName = "Fill Data Table from JSON File", Category = "DataTable")
		static bool FillDataTableFromJSONFile(UDataTable* DataTable, const FString& JSONFilePath);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Table As CSV String", Category = "DataTable")
		static void GetDataTableAsCSVString(UDataTable* DataTable, FString& CSVString);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Table As CSV File", Category = "DataTable")
		static void GetDataTableAsCSVFile(UDataTable* DataTable, const FString& CSVFilePath);



};
