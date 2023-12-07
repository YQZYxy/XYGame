#pragma once

#include "Logging/LogMacros.h"

class UObject;

YQZY_API DECLARE_LOG_CATEGORY_EXTERN(AYQZYLog, Log, All);
#define YQZYDebug(format, ...) UE_LOG(AYQZYLog, Log, TEXT(format), ##__VA_ARGS__)
#define YQZYWarning(format, ...) UE_LOG(AYQZYLog, Warning, TEXT(format), ##__VA_ARGS__)
#define YQZYError(format, ...) UE_LOG(AYQZYLog, Error, TEXT(format), ##__VA_ARGS__)
#define YQZYFatal(format, ...) UE_LOG(AYQZYLog, Fatal, TEXT(format), ##__VA_ARGS__)

YQZY_API FString GetClientServerContextString(UObject* ContextObject = nullptr);