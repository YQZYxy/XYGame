#pragma once

#include "Logging/LogMacros.h"

class UObject;

YQZY_API DECLARE_LOG_CATEGORY_EXTERN(YQZYLog, Log, All);
#define YQZYDebug(format, ...) UE_LOG(YQZYLog, Log, "[%s::<%d>] " TEXT(format), TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define YQZYWarning(format, ...) UE_LOG(YQZYLog, Warning, "[%s::<%d>] " TEXT(format), TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define YQZYError(format, ...) UE_LOG(YQZYLog, Error, "[%s::<%d>] " TEXT(format), TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define YQZYFatal(format, ...) UE_LOG(YQZYLog, Fatal, "[%s::<%d>] " TEXT(format), TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)

YQZY_API FString GetClientServerContextString(UObject* ContextOYQZYLogbject = nullptr);


#define GE_DEBUG_ITC(id,time,color, info)\
GEngine->AddOnScreenDebugMessage(id, time, color, TEXT(#info));

#define GE_DEBUG_TC(time,color, info)\
GE_DEBUG_ITC(-1, time,color,info)

#define GE_DEBUG(info)\
GE_DEBUG_ITC(-1, 3.0, FColor::Green,info)
