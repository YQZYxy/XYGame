#pragma once

#include "Logging/LogMacros.h"

class UObject;

YQZY_API DECLARE_LOG_CATEGORY_EXTERN(YQZYLog, Log, All);
#define YQZYDebug(format, ...) UE_LOG(YQZYLog, Log, TEXT(format), ##__VA_ARGS__)
#define YQZYWarning(format, ...) UE_LOG(YQZYLog, Warning, TEXT(format), ##__VA_ARGS__)
#define YQZYError(format, ...) UE_LOG(YQZYLog, Error, TEXT(format), ##__VA_ARGS__)
#define YQZYFatal(format, ...) UE_LOG(YQZYLog, Fatal, TEXT(format), ##__VA_ARGS__)

YQZY_API FString GetClientServerContextString(UObject* ContextOYQZYLogbject = nullptr);