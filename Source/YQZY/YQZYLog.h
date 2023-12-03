#pragma once

#include "Logging/LogMacros.h"

class UObject;

YQZY_API DECLARE_LOG_CATEGORY_EXTERN(YQZYLog, Log, All);
#define LogDebug(format, ...) UE_LOG(YQZYLog, Log, TEXT(format), ##__VA_ARGS__)
#define LogWarning(format, ...) UE_LOG(YQZYLog, Warning, TEXT(format), ##__VA_ARGS__)
#define LogError(format, ...) UE_LOG(YQZYLog, Error, TEXT(format), ##__VA_ARGS__)
#define LogFatal(format, ...) UE_LOG(YQZYLog, Fatal, TEXT(format), ##__VA_ARGS__)

YQZY_API FString GetClientServerContextString(UObject* ContextObject = nullptr);