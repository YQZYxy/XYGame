#pragma once

#include "Logging/LogMacros.h"

class UObject;

YQZY_API DECLARE_LOG_CATEGORY_EXTERN(YQZYLog, Log, All);


#if PLATFORM_LINUX || PLATFORM_ANDROID
#define YQZYDebug(format, ...) UE_LOG(YQZYLog, Log, TEXT("[%s<%d>]  " format), *FString(__FUNCTION__),  __LINE__, ##__VA_ARGS__)
#define YQZYWarning(format, ...) UE_LOG(YQZYLog, Warning,TEXT("[%s<%d>]  " format), *FString(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define YQZYError(format, ...) UE_LOG(YQZYLog, Error, TEXT("[%s<%d>]  " format), *FString(__FUNCTION__),  __LINE__, ##__VA_ARGS__)
#define YQZYFatal(format, ...) UE_LOG(YQZYLog, Fatal, TEXT("[%s<%d>]  " format), *FString(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#endif

#if PLATFORM_WINDOWS
#define YQZYDebug(format, ...) UE_LOG(YQZYLog, Log, TEXT("[%s<%d>] " format), TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define YQZYWarning(format, ...) UE_LOG(YQZYLog, Warning, TEXT("[%s<%d>] " format), TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define YQZYError(format, ...) UE_LOG(YQZYLog, Error, TEXT("[%s<%d>] " format), TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define YQZYFatal(format, ...) UE_LOG(YQZYLog, Fatal, TEXT("[%s<%d>] " format), TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#endif

YQZY_API FString GetClientServerContextString(UObject* ContextOYQZYLogbject = nullptr);


#define GE_DEBUG_ITC(id,time,color, format, ...)\
GEngine->AddOnScreenDebugMessage(id, time, color, FString::Printf(TEXT(format), ##__VA_ARGS__));

#define GE_DEBUG_TC(time,color, format, ...)\
GE_DEBUG_ITC(-1, time,color,format,##__VA_ARGS__)

#define GE_DEBUG(format, ...)\
GE_DEBUG_ITC(-1, 1.0, FColor::Green,format,##__VA_ARGS__)
