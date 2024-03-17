#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
//#include "Game/Config/LogicConfig.h"
#include "LogicConfigSubsystem.generated.h"

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
	if(class_config_map.Contains(#class_type))						\
	{																\
		YQZYFatal(#class_type);										\
	}																\
	class_config_map.Add(#class_type, NewObject<class_type>());		\
}

#define DEF_CONFIG(class_type)										\
	UFUNCTION(BlueprintCallable, Category = "LogicConfigSubsystem")	\
	class_type* Get##class_type() const 							\
{																	\
	auto ptr = m_class_config_map.Find(#class_type);				\
	if (!ptr)return nullptr; 										\
	return (class_type*)*ptr;										\
}

#define LCS_SUB(world) ULogicConfigSubsystem::GetLogicConfigSubsystem(world)

#define LCS_SUB_CFG(world,class_type) LCS_SUB(world) ? LCS_SUB(world)->Get##class_type():nullptr;


class ULogicConfig;
class UWeaponConfig;
class UTaskConfig;


UCLASS(Config = Game)
class YQZY_API ULogicConfigSubsystem  : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	ULogicConfigSubsystem();
	
	//在InitObject里面添加 DEF_CONFIG 对应 NEW_CONFIG类型
	DEF_CONFIG(UWeaponConfig);
	DEF_CONFIG(UTaskConfig);

private:
	static bool InitObject(TMap<FName, ULogicConfig*>& class_config_map);

public:
    virtual bool ShouldCreateSubsystem(UObject* Outer) const;
	virtual void Initialize(FSubsystemCollectionBase& Collection);
	virtual void Deinitialize();

	UFUNCTION(BlueprintCallable, Category = "AYQZYLogicConfigSubsystem")
	static ULogicConfigSubsystem* GetLogicConfigSubsystem(UWorld* world);

	UFUNCTION(BlueprintCallable, Category = "AYQZYLogicConfigSubsystem")
	static bool OnReload(ULogicConfigSubsystem* in);

	UFUNCTION(BlueprintCallable, Category = "AYQZYLogicConfigSubsystem")
	static bool LoadCfg(TMap<FName, ULogicConfig*>& class_config_map, const TMap<FName, FName>& data_path_map);

	UFUNCTION(BlueprintCallable, Category = "AYQZYLogicConfigSubsystem")
	ULogicConfig* GetConfigByName(FName class_name);

	UFUNCTION(BlueprintCallable, Category = "AYQZYLogicConfigSubsystem")
	TMap<FName, FName>& GetPathMap() {return m_data_path_map;}

	UFUNCTION(BlueprintCallable, Category = "AYQZYLogicConfigSubsystem")
	bool SetClassConfigMap(const TMap<FName, ULogicConfig*>& class_config_map);

private:
	bool InitPath();


	UPROPERTY()
	TMap<FName, FName> m_data_path_map;
	UPROPERTY()
	TMap<FName, ULogicConfig*> m_class_config_map;

public:
	
	//动态读取DataTable数据表格
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
