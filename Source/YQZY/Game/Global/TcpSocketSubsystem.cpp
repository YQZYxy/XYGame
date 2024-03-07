#include "TcpSocketSubsystem.h"
#include "YQZYLog.h"

//begin
#include "Sockets.h"
#include "Internationalization/Text.h"
#include "Misc/OutputDevice.h"
#include "Internationalization/Internationalization.h"
#include "Common/TcpSocketBuilder.h"
//end

#include "proto/pb_role.pb.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TcpSocketSubsystem)


bool UTcpSocketSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}
 
void UTcpSocketSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	m_Socket = nullptr;

	this->ConnectToServer("192.168.3.101", 3724);
}
 
void UTcpSocketSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

//void UTcpSocketSubsystem::Shutdown()
//{
//	m_NativeSocket = FWebSocketsModule::Get().CreateWebSocket("ws://192.168.3.101:3723/webSocketServer/ue");
//
//	m_NativeSocket->OnConnected().AddUObject(this, &UTcpSocketSubsystem::OnConnected);
//	m_NativeSocket->OnConnectionError().AddUObject(this, &UTcpSocketSubsystem::OnConnectionError);
//	m_NativeSocket->OnClosed().AddUObject(this, &UTcpSocketSubsystem::OnClosed);
//	m_NativeSocket->OnMessage().AddUObject(this, &UTcpSocketSubsystem::OnMessage);
//	m_NativeSocket->OnMessageSent().AddUObject(this, &UTcpSocketSubsystem::OnMessageSent);
//
//	m_NativeSocket->OnRawMessage().AddUObject(this, &UTcpSocketSubsystem::OnRawMessage);
//
//	m_NativeSocket->Connect();
//	m_NativeSocket->Send(Message.GetData(), sizeof(uint8) * Message.Num(), true);
//	m_NativeSocket->Send(Message);
//
//    if (m_NativeSocket->IsConnected()) {
//		m_NativeSocket->Close();
//	} 
//	Super::Shutdown();
//
//}


bool UTcpSocketSubsystem::ConnectToServer(const FString& IP, int32 Port)
{
	if (m_Socket)
	{
		m_Socket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(m_Socket);
		m_Socket = nullptr;
	}

	TSharedPtr<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	if(nullptr == Addr)
	{
		YQZYError("InValid CreateInternetAddr");
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("InValid CreateInternetAddr"));
		return false;
	}

	bool bIsValid;
	Addr->SetIp(*IP, bIsValid);
	Addr->SetPort(Port);

	if (!bIsValid)
	{
		YQZYError("InValid IP Address");
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("InValid IP Address"));
		return false;
	}
	m_Socket = FTcpSocketBuilder(TEXT("TcpClient")).AsBlocking().WithReceiveBufferSize(2 * 1024 * 1024);

	bool bConnected = m_Socket->Connect(*Addr);
	if (!bConnected)
	{
		YQZYError("Failed Connect To Server");
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, TEXT("Failed Connect To Server"));
		return false;
	}
	
	YQZYDebug("Success Connect To Server");
	//GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, TEXT("Success Connect To Server"));
	GE_DEBUG( 5.0, FColor::Green, "Success Connect To Server");

	return true;

}

bool UTcpSocketSubsystem::SendToServer(TArray<uint8> SendData)
{
	if(nullptr == Addr)
	{
		YQZYError("m_Socket is not connected!");
		return false;
	}

	// 发送数据部分
	int32 SentBytes = 0;
	bool bSuccess = m_Socket->Send(SendData.GetData(), SendData.Num(), SentBytes);

	if (!bSuccess || SentBytes != SendData.Num())
	{
		YQZYError("Failed to send data!");
		return false;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, TEXT("Success to send data!"));
	YQZYDebug("Success to send data!");
	return true;
}

bool UTcpSocketSubsystem::DisConnectToServer()
{
	if (m_Socket)
	{
		m_Socket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(m_Socket);
		m_Socket = nullptr;
		return true;
	}
	return false;
}

TArray<uint8> UTcpSocketSubsystem::ReceiveToServer()
{
	TArray<uint8> Bytes;

	if (m_Socket)
	{
		uint32 Size;
		while (m_Socket->HasPendingData(Size))
		{
			Bytes.SetNumUninitialized(FMath::Min(Size, 65507u));

			int32 ReadBytes = 0;
			// 读取数据到字节流中
			m_Socket->Recv(Bytes.GetData(), Bytes.Num(), ReadBytes);

			// 将实际读取的部分截取出来
			Bytes.SetNum(ReadBytes);

			// 如果需要等待接收完整数据再返回，可以设置一个条件，比如接收到特定结束标志
			// 如果已经接收到完整数据，可以直接返回
			return Bytes;
		}
	}

	// 如果没有接收到数据，返回空字节流
	return TArray<uint8>();
}


bool UTcpSocketSubsystem::StringToBytes(FString InString, TArray<uint8>& OutBytesArray)
{
	OutBytesArray.Empty();

	if (!InString.IsEmpty())
	{
		FTCHARToUTF8 Converter(*InString);
		int32 NumBytes = Converter.Length();
		if (NumBytes > 0)
		{
			OutBytesArray.Append((uint8*)Converter.Get(), NumBytes);
			return true;
		}
	}

	return false;
}

bool UTcpSocketSubsystem::DataTypeToJSON(int32 Int, bool Inbool, FString String, FVector Vector, TArray<int32> Array, TArray<uint8>& OutBytesArray)
{
	OutBytesArray.Empty();

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	JsonObject->SetNumberField("MyInteger", Int);
	JsonObject->SetBoolField("MyBool", Inbool);
	JsonObject->SetStringField("MyString", String);

	TSharedPtr<FJsonObject> VectorObject = MakeShareable(new FJsonObject);
	JsonObject->SetNumberField("MyVector", Vector.X);
	JsonObject->SetNumberField("MyVector", Vector.Y);
	JsonObject->SetNumberField("MyVector", Vector.Z);

	JsonObject->SetObjectField("MyVector", VectorObject);

	TArray<TSharedPtr<FJsonValue>> JsonArray;
	for (auto& value : Array)
	{
		JsonArray.Add(MakeShareable(new FJsonValueNumber(value)));
	}
	JsonObject->SetArrayField("Array", JsonArray);

	// 将 JSON 对象转换为字符串  
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
	{
		Writer->Close();

		// 将字符串转换为字节数组  
		FTCHARToUTF8 Converter(*OutputString);
		int32 NumBytes = Converter.Length();
		if (NumBytes > 0)
		{
			OutBytesArray.Append((uint8*)Converter.Get(), NumBytes);
			return true;
		}
	}

	return false;
}


void UTcpSocketSubsystem::BytesToString(TArray<uint8> InBytesArray, FString& OutString)
{
	// 检查字节数组是否为空
	if (InBytesArray.Num() == 0)
	{
		OutString.Empty();
		GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Blue, TEXT("data = null"));
		YQZYError("", TEXT("data = null"));
		return;
	}

	// 将字节流转换为UTF-8字符串
	FString Utf8String = FUTF8ToTCHAR(reinterpret_cast<const ANSICHAR*>(InBytesArray.GetData()), InBytesArray.Num()).Get();

	// 在这里你可以使用Utf8String进行其他操作，例如将其转换为JSON对象
	// 注意：在UE5中，你可能需要使用FJsonSerializer的Deserialize方法
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Utf8String);

	// Deserialize JSON
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		// 在这里可以使用JsonObject进行其他操作
	}
	else
	{
		// JSON解析失败的处理
		YQZYError("", TEXT("Failed to parse JSON from string"));
	}

	// 将最终的JSON字符串赋值给输出参数
	OutString = Utf8String;
}

 