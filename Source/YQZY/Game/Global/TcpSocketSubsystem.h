#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TcpSocketSubsystem.generated.h"

UCLASS(Config = Game)
class YQZY_API UTcpSocketSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
    virtual bool ShouldCreateSubsystem(UObject* Outer) const;
	virtual void Initialize(FSubsystemCollectionBase& Collection);
	virtual void Deinitialize();


public:
	// TcpSocket
	UFUNCTION(BlueprintCallable, Category = "TcpSocketSubsystem")
	 bool ConnectToServer(const FString& IP, int32 Port = 8888);

	UFUNCTION(BlueprintCallable, Category = "TcpSocketSubsystem")
	 bool SendToServer(const TArray<uint8>& SendData, int32 msg_type = -1);

	UFUNCTION(BlueprintCallable, Category = "TcpSocketSubsystem")
	 bool DisConnectToServer();

	UFUNCTION(BlueprintCallable, Category = "TcpSocketSubsystem")
	 TArray<uint8> ReceiveToServer();


	UFUNCTION(BlueprintCallable, Category = "TcpSocketSubsystem")
	static bool StringToBytes(FString InString, TArray<uint8>& OutBytesArray);

	UFUNCTION(BlueprintCallable, Category = "TcpSocketSubsystem")
	static bool DataTypeToJSON(int32 Int, bool Inbool, FString String, FVector Vector, TArray<int32> Array, TArray<uint8>& OutBytesArray);

	UFUNCTION(BlueprintCallable, Category = "TcpSocketSubsystem")
	static void BytesToString(TArray<uint8> InBytesArray, FString& OutString);

	int32 Tcphtonl(int32 x) {
		union {
			int32 result;
			int8 result_array[4];
		};
		result_array[0] = static_cast<uint8>(x >> 24);
		result_array[1] = static_cast<uint8>((x >> 16) & 0xFF);
		result_array[2] = static_cast<uint8>((x >> 8) & 0xFF);
		result_array[3] = static_cast<uint8>(x & 0xFF);
		return result;
	}
public:	
	//// WebSocket
	//void OnConnected();
	//void OnConnectionError(const FString& Error);
	//void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
	//void OnMessage(const FString& Message);
	//void OnMessageSent(const FString& MessageString);
	//void OnRawMessage();


private:
	class FSocket* m_Socket;

	UPROPERTY()
	TArray<uint8> m_MsgBuf;
};
