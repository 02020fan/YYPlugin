// Fill out your copyright notice in the Description page of Project Settings.


#include "UDPSubsystem.h"

#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Common/UdpSocketBuilder.h"

bool UUDPSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UUDPSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUDPSubsystem::Deinitialize()
{
	Super::Deinitialize();
	if (SenderSocket)
	{
		SenderSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(SenderSocket);
	}
}


bool UUDPSubsystem::StartUDPSender(const FString& Socketname, const FString& IP, const int32 port, bool UDP)
{
	RemoteAddr=ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid;
	RemoteAddr->SetIp(*IP,bIsValid);
	RemoteAddr->SetPort(port);
	if (!bIsValid)
	{
		UE_LOG(LogTemp,Warning,TEXT("UDP Sender ip Error: %s"),*IP);
		return false;
	}

	SenderSocket=FUdpSocketBuilder(*Socketname)
	.AsReusable()
	.WithBroadcast()
	.WithSendBufferSize(2*1024*1024);

	int32 SendSize=2*1024*1024;
	SenderSocket->SetSendBufferSize(SendSize,SendSize);
	SenderSocket->SetReceiveBufferSize(SendSize,SendSize);
	if (bIsValid)
	{
		bIsValid=true;
	}
	return bIsValid;
}

bool UUDPSubsystem::UDP_SendString(FString ToSend)
{
	
	if (!SenderSocket)
	{
		UE_LOG(LogTemp, Warning, TEXT("No sender socket"));
		return false;
	}
	//消息处理
	int32 BytesSent = 0;
	FString serialized = ToSend;
	TCHAR* serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;
	SenderSocket->SendTo((uint8*)TCHAR_TO_UTF8(serializedChar), size, BytesSent, *RemoteAddr);
	if (BytesSent < 0)
	{
		const FString Str = "Socket is valid but the receiver received 0 bytes, make sure it is listening properly!";
		UE_LOG(LogTemp, Error, TEXT("%s"), *Str);
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("UDP Send Succcess! INFO Sent = %s "), *ToSend);

	return true;

}

