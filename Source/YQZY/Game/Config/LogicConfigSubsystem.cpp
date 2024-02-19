#include "LogicConfigSubsystem.h"
#include "YQZYLog.h"
#include "LogicConfig.h"
#include "Game/Config/Weaponconfig/WeaponConfig.h"
#include "Game/Config/TaskConfig/TaskConfig.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LogicConfigSubsystem)

ULogicConfigSubsystem::ULogicConfigSubsystem()
{
	//添加
	NEW_CONFIG(UWeaponConfig);
	NEW_CONFIG(UTaskConfig);


	this->InitPath();
}


// static ULogicConfigSubsystem* logic_config_manager_ptr = nullptr;
// ULogicConfigSubsystem* ULogicConfigSubsystem::GetLogicConfigManagerInstance()
// {
// 	if (!logic_config_manager_ptr)
// 	{
// 		logic_config_manager_ptr = NewObject<ULogicConfigSubsystem>();
// 		if (!logic_config_manager_ptr->Init())
// 		{
// 			logic_config_manager_ptr->MarkAsGarbage();
// 			GEngine->ForceGarbageCollection(true);
// 			logic_config_manager_ptr = nullptr;
// 			return nullptr;
// 		}
// 		logic_config_manager_ptr->AddToRoot();
// 	}

// 	return logic_config_manager_ptr;
// }

// void ULogicConfigSubsystem::DeleteUObject()
// {
// 	if (logic_config_manager_ptr)
// 	{
// 		logic_config_manager_ptr->m_data_path_map.Empty();
// 		logic_config_manager_ptr->m_class_config_map.Empty();
// 		logic_config_manager_ptr->RemoveFromRoot();
// 		logic_config_manager_ptr = nullptr;
// 	}
// }

// bool ULogicConfigSubsystem::OnReload()
// {
// 	ULogicConfigSubsystem* temp_ptr = NewObject<ULogicConfigSubsystem>();
// 	if (temp_ptr && !temp_ptr->Init())
// 	{
// 		temp_ptr->MarkAsGarbage();
// 		GEngine->ForceGarbageCollection(true);
// 		return false;
// 	}
// 	temp_ptr->AddToRoot();

// 	if (logic_config_manager_ptr)
// 	{
// 		logic_config_manager_ptr->RemoveFromRoot();
// 		logic_config_manager_ptr->MarkAsGarbage();
// 		GEngine->ForceGarbageCollection(true);
// 		logic_config_manager_ptr = nullptr;
// 	}

// 	logic_config_manager_ptr = temp_ptr;

// 	return true;
// }

bool ULogicConfigSubsystem::OnReload()
{
	TMap<FName, ULogicConfig*> class_config_map; 
	
	return true;
}

ULogicConfigSubsystem* ULogicConfigSubsystem::GetLogicConfigSubsystem(UWorld* world)
{
	UGameInstance* GameInstance = world ? world->GetGameInstance() : nullptr;
	return GameInstance ? GameInstance->GetSubsystem<ULogicConfigSubsystem>() : nullptr;
}

ULogicConfig* ULogicConfigSubsystem::GetConfigByName(FName class_name)
{
	auto it = m_class_config_map.Find(class_name);
	if (nullptr == it)
	{
		return nullptr;
	}

	return *it;
}

bool ULogicConfigSubsystem::InitPath()
{	
	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/Config/ConfigManager.ConfigManager'")); ///Script/Engine.DataTable'
	if (!pDataTable)
	{
		YQZYError("ULogicConfigSubsystem LoadObject NULL ");
		return false;
	}
	FString ContextString;
	TArray<FName> RowNames;
	RowNames = pDataTable->GetRowNames();
	for (auto& name : RowNames)
	{
		FLogicConfigManagerData* pRow = pDataTable->FindRow<FLogicConfigManagerData>(name, ContextString);
		if (nullptr == pRow)
		{
			return false;
		}

		if (pRow->class_type.IsNone() || pRow->path.IsNone())
		{
			YQZYError("read by row name --- RowName:%s, ID:%d, max_num:%d  error");
			return false;
		}

		m_data_path_map.Add(pRow->class_type, pRow->path);
	}

	return true;
}

bool ULogicConfigSubsystem::Init()
{
	for (auto& it_config : m_class_config_map)
	{
		if (nullptr == it_config.Value)
		{
			YQZYError("config: %s is nullptr", it_config.Key);
			return false;
		}
	}

	for (auto& table_data : m_data_path_map)
	{
		auto it = m_class_config_map.Find(table_data.Key);
		if (nullptr == it)
		{
			YQZYError("%s %d Init Cfg %s ", __FUNCTION__, __LINE__, *table_data.Value.ToString());
			return false;
		}
		ULogicConfig* cfg = (ULogicConfig*)*it;
		if (nullptr == cfg)
		{
			YQZYError("%s %d Init Cfg %s ", __FUNCTION__, __LINE__, *table_data.Value.ToString());
			return false;
		}
		FString error;

		if (!cfg->Init(table_data.Value, error))
		{
			YQZYError("error_info[ %s ]", *error);
			return false;
		}
	}

	return true;
}




/////////////////////////////////////////////////////////////////////////////////////////////

bool ULogicConfigSubsystem::FillDataTableFromCSVString(UDataTable* DataTable, const FString& CSVString)
{
	if (!DataTable || (CSVString.Len() == 0))
	{

		return false;
	}
	// Call bulit-in function
	TArray<FString> Errors = DataTable->CreateTableFromCSVString(CSVString);
	if (Errors.Num())
	{
		// It has some error message
		for (const FString& Error : Errors)
		{
			UE_LOG(LogTemp, Warning, TEXT("error1"));
		}
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("true"));
	return true;

}

bool ULogicConfigSubsystem::FillDataTableFromCSVFile(UDataTable* DataTable, const FString& CSVFilePath)
{
	FString CSVString;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*CSVFilePath))
	{
		// Supports all combination of ANSI/Unicode files and platforms.
		FFileHelper::LoadFileToString(CSVString, *CSVFilePath);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("error2"));
		return false;
	}
	return ULogicConfigSubsystem::FillDataTableFromCSVString(DataTable, CSVString);
	UE_LOG(LogTemp, Warning, TEXT("success"));
}

bool ULogicConfigSubsystem::FillDataTableFromJSONString(UDataTable* DataTable, const FString& JSONString)
{
	if (!DataTable || (JSONString.Len() == 0))
	{

		return false;
	}
	// Call bulit-in function
	TArray<FString> Errors = DataTable->CreateTableFromJSONString(JSONString);

	if (Errors.Num())
	{
		// It has some error message
		for (const FString& Error : Errors)
		{

		}
		return false;
	}

	return true;
}

bool ULogicConfigSubsystem::FillDataTableFromJSONFile(UDataTable* DataTable, const FString& JSONFilePath)
{
	FString JSONString;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*JSONFilePath))
	{
		// Supports all combination of ANSI/Unicode files and platforms.
		FFileHelper::LoadFileToString(JSONString, *JSONFilePath);
	}
	else
	{

		return false;
	}
	return ULogicConfigSubsystem::FillDataTableFromJSONString(DataTable, JSONString);
}

void ULogicConfigSubsystem::GetDataTableAsCSVString(UDataTable* DataTable, FString& CSVString)
{
	CSVString = FString();

	if (!DataTable || (DataTable->RowStruct == nullptr))
	{

		return;
	}

	// First build array of properties
	TArray<FProperty*> StructProps;
	for (TFieldIterator<FProperty> It(DataTable->RowStruct); It; ++It)
	{
		FProperty* Prop = *It;
		check(Prop != nullptr);
		StructProps.Add(Prop);
	}

	// First row, column titles, taken from properties
	CSVString += TEXT("---");
	for (int32 PropIdx = 0; PropIdx < StructProps.Num(); PropIdx++)
	{
		CSVString += TEXT(",");
		CSVString += StructProps[PropIdx]->GetName();
	}
	CSVString += TEXT("\n");

	// Now iterate over rows
	for (auto RowIt = DataTable->GetRowMap().CreateConstIterator(); RowIt; ++RowIt)
	{
		FName RowName = RowIt.Key();
		CSVString += RowName.ToString();

		uint8* RowData = RowIt.Value();
		for (int32 PropIdx = 0; PropIdx < StructProps.Num(); PropIdx++)
		{
			CSVString += TEXT(",");
			CSVString += DataTableUtils::GetPropertyValueAsString(StructProps[PropIdx], RowData, EDataTableExportFlags::None);
		}
		CSVString += TEXT("\n");
	}
}

void ULogicConfigSubsystem::GetDataTableAsCSVFile(UDataTable* DataTable, const FString& CSVFilePath)
{
	FString CSVString;
	ULogicConfigSubsystem::GetDataTableAsCSVString(DataTable, CSVString);
	if (CSVString.Len() == 0)
	{
		return;
	}
	FFileHelper::SaveStringToFile(CSVString, *CSVFilePath, FFileHelper::EEncodingOptions::ForceUTF8);
}