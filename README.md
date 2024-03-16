--2023-12-7 22:10:20
ResonanceAudio.uplugin  插件默认设为false

Object->Actor+Component->Level->World->WorldContext->GameInstance->Engine

InstalledBuild.txt          // 发版
SourceDistribution.txt      // 源码版

D:\UEEditors\UE5.3.2\UnrealEngine\Engine\Source\Runtime\ApplicationCore\Private\Windows\WindowsPlatformApplicationMisc.cpp 	//TRACE_CPUPROFILER_EVENT_SCOPE(WinPumpMessages);


3.3 FString To Array[uint8]
//方法1
FString JsonStr;  
TArray<uint8> content;  
content.SetNum(JsonStr.Len());  
memcpy(content.GetData(), TCHAR_TO_ANSI(*JsonStr), JsonStr.Len());
//方法2
FString StrData;  
const TCHAR* StrPtr = *StrData;  
FTCHARToUTF8 UTF8String(StrPtr);  
int32 CTXSize = UTF8String.Length();
TArray<uint8> URLData;  
URLData.SetNum(CTXSize);  
memcpy(URLData.GetData(), UTF8String.Get(), CTXSize);
​
3.4 FString To char*
FString TheString = "Hello，world";
char* MyCharPtr = TCHAR_TO_UTF8(*MyFString);

3.5 FString To const char *
const char *plainText= TCHAR_TO_ANSI(*aes_content);

3.6 FString To TCHAR*
FString s="a";
TCHAR* t=*s;

3.7 FString To std::string
#include <string>
FString UE4Str = TEXT("Flowers");
std::string MyStdString = TCHAR_TO_UTF8(*UE4Str);

3.9 FString To bool
FString TheString = "123.021";
bool MyBool = MyFString.ToBool();

3.10 FString To int32
FString TheString = "123.021";
//注意，Atoi和Atof是静态函数，所以使用语法FCString：：TheFunction调用它：
int32 MyShinyNewInt = FCString::Atoi(*TheString);

3.11 FString To int64
FString TheString = "12312345678789561234879";
//注意，Atoi64是静态函数，所以使用语法FCString::TheFunction调用它：
int64 MyShinyNewInt = FCString::Atoi64(*TheString);

3.12 FString To float
FString TheString = "123.021";
//注意，Atoi和Atof是静态函数，所以使用语法FCString：：TheFunction调用它：
float MyShinyNewFloat = FCString::Atof(*TheString);

3.13 FString To double
FString TheString = "123.021";
//注意，Atod是静态函数，所以使用语法FCString：：TheFunction调用它
double MyShinyNewFloat = FCString::Atod(*TheString);
//FString转String转Double
FString str = "113.5246854";
std::string numString = TCHAR_TO_UTF8(*str);
double b = atof(numString.c_str());


3.18 Array[uint8] to FString
TArray<uint8> content;  
const std::string cstr(reinterpret_cast<const char*>(content.GetData()), content.Num());  
FString frameAsFString = cstr.c_str();  
UE_LOG(VRSLog, Warning, TEXT("%s"), *frameAsFString); 

六、TChar*
TChar* 与 char* 的互相转换
主要是使用下面的四个宏定义。
TCHAR_TO_ANSI(*str)
ANSI_TO_TCHAR(*str)  
TCHAR_TO_UTF8(*str)  
UTF8_TO_TCHAR(*str)

六、TChar*
TChar* 与 char* 的互相转换
主要是使用下面的四个宏定义。
TCHAR_TO_ANSI(*str)
ANSI_TO_TCHAR(*str)  
TCHAR_TO_UTF8(*str)  
UTF8_TO_TCHAR(*str)

八、char*
char* To FString
FString MyFString = FString(UTF8_TO_TCHAR(MyCharPtr));