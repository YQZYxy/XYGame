#include "TcpSocketSubsystem.h"
#include "YQZYLog.h"

//begin
#include "Sockets.h"
#include "Internationalization/Text.h"
#include "Misc/OutputDevice.h"
#include "Internationalization/Internationalization.h"
#include "Common/TcpSocketBuilder.h"
//end

#include "Protobuf/role_data.pb.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TcpSocketSubsystem)

	// //序列化：
	// bool SerializeToOstream(ostream* output) const;
	// bool SerializeToArray(void *data, int size) const;
	// bool SerializeToString(string* output) const;

	// //反序列化：
	// bool ParseFromIstream(istream* input);
	// bool ParseFromArray(const void* data, int size);
	// bool ParseFromString(const string& data);

bool UTcpSocketSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}
 
void UTcpSocketSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	m_Socket = nullptr;

	this->ConnectToServer("192.168.3.102", 3723);

	Role_Data RoleData ;
	
	RoleData.set_role_id(9527);
	RoleData.set_role_name("桂林仔");



	std::string msg_str;
	RoleData.SerializeToString(&msg_str);

	FString HappyString(msg_str.c_str());

	static TArray<uint8> temp_msg;
	UTcpSocketSubsystem::StringToBytes(HappyString, temp_msg);

	static TArray<uint8> msg; msg.Empty();
	static int32 msg_type = 100;
	for (int i = 0; i < 4; ++i)
	{
		msg.Emplace(*((uint8*)&msg_type + i));
	}

	msg.Append(temp_msg);

	this->SendToServer(msg);
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
	if(nullptr == m_Socket)
	{
		YQZYError("m_Socket is not connected!");
		return false;
	}

	static TArray<uint8> msg; msg.Empty();
	static int32 msg_length = SendData.Num();
	for(int i= 0; i < 4; ++i)
	{
		msg.Emplace(*((uint8 *)&msg_length + i));
	}
	msg.Append(SendData);


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
	static TArray<uint8> msg_buf;

	if (m_Socket)
	{
		uint32 Size;
		while (m_Socket->HasPendingData(Size))
		{
			// msg_buf.SetNumUninitialized(FMath::Min(Size, 65535u));

			// int32 ReadMsgLeft = 0;
			// m_Socket->Recv(msg_buf.GetData(), msg_buf.Num() , ReadMsgLeft);
			// msg_buf.SetNum(ReadMsgLeft);
			
			int32 TempLeft = 0;
			static TArray<uint8> temp_length;
			int32 ReadMsgLeft = 0;
			m_Socket->Recv(temp_length.GetData(), 4 , TempLeft);

			if(4 > TempLeft)
			{
				return TArray<uint8>();
			}

			{
				*((uint8*)&ReadMsgLeft + 0) = temp_length[0];
				*((uint8*)&ReadMsgLeft + 1) = temp_length[1];
				*((uint8*)&ReadMsgLeft + 2) = temp_length[2];
				*((uint8*)&ReadMsgLeft + 3) = temp_length[3];
			}

			if ( 4 > ReadMsgLeft)
			{
				return TArray<uint8>();
			}

			//nLeft = static_cast<int32>(int32(msg_buf[3]) << 24 | int32(msg_buf[2]) << 16 | int32(msg_buf[1]) << 8 | int32(msg_buf[0]));
			int32 nLeft = ReadMsgLeft;
			int32 nread = 0;
			int32 index = 0;
			
			while (nLeft > 0)
			{
				m_Socket->Recv(msg_buf.GetData() + index, nLeft , nread);
				if(0 >= nread)
				{
					return TArray<uint8>();
				}
				
				index += nread;
				nLeft -= nread;
			}

			return msg_buf;
		}
	}

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

 