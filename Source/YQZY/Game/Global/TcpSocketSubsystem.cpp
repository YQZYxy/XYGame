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

void UTcpSocketSubsystem::OnTest()
{
    P_RoleData root;

    m_NativeSocket = FWebSocketsModule::Get().CreateWebSocket(m_Url);

    m_NativeSocket->OnConnected().AddUObject(this, &UInWebSocketSession::OnConnected);
    m_NativeSocket->OnClosed().AddUObject(this, &UInWebSocketSession::OnClosed);
    m_NativeSocket->OnMessage().AddUObject(this, &UInWebSocketSession::OnMessage);
    m_NativeSocket->OnRawMessage().AddUObject(this, &UInWebSocketSession::OnRawMessage);
    m_NativeSocket->OnConnectionError().AddUObject(this, &UInWebSocketSession::OnError);

    m_NativeSocket->Connect();
    m_NativeSocket->Send(Message.GetData(), sizeof(uint8) * Message.Num(), bIsBinary);
    m_NativeSocket->Send(Message);
}