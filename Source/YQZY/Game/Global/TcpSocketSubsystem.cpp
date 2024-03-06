#include "TcpSocketSubsystem.h"
#include "YQZYLog.h"

#include "proto/p_role.pb.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TcpSocketSubsystem)


bool UTcpSocketSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}
 
void UTcpSocketSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}
 
void UTcpSocketSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UTcpSocketSubsystem::Shutdown()
{
    if (m_NativeSocket->IsConnected()) {
		m_NativeSocket->Close();
	} 
	Super::Shutdown();
}

void UTcpSocketSubsystem::OnTest()
{
    P_RoleData root;

    m_NativeSocket = FWebSocketsModule::Get().CreateWebSocket("ws://192.168.3.101:3723/webSocketServer/ue");

    m_NativeSocket->OnConnected().AddUObject(this, &UTcpSocketSubsystem::OnConnected);
    m_NativeSocket->OnConnectionError().AddUObject(this, &UTcpSocketSubsystem::OnConnectionError);
    m_NativeSocket->OnClosed().AddUObject(this, &UTcpSocketSubsystem::OnClosed);
    m_NativeSocket->OnMessage().AddUObject(this, &UTcpSocketSubsystem::OnMessage);
    m_NativeSocket->OnMessageSent().AddUObject(this, &UTcpSocketSubsystem::OnMessageSent);

    m_NativeSocket->OnRawMessage().AddUObject(this, &UTcpSocketSubsystem::OnRawMessage);

    m_NativeSocket->Connect();
    m_NativeSocket->Send(Message.GetData(), sizeof(uint8) * Message.Num(), bIsBinary);
    m_NativeSocket->Send(Message);
}

void UUWebSocketGameInstance::OnConnected()
{

}

void UUWebSocketGameInstance::OnConnectionError(const FString& Error)
{

}

void UUWebSocketGameInstance::OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{

}
void UUWebSocketGameInstance::OnMessage(const FString& Message)
{

}

void UUWebSocketGameInstance::OnMessageSent(const FString& MessageString)
{
    
}

void UUWebSocketGameInstance::OnRawMessage()
{

}


 