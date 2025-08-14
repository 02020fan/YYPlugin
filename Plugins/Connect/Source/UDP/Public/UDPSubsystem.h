// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UDPSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UDP_API UUDPSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
public:
	FSocket* SenderSocket;

	TSharedPtr<FInternetAddr> RemoteAddr;

	UFUNCTION(BlueprintCallable, Category = "UDP")
	bool StartUDPSender(const FString& Socketname,const FString& IP,const int32 port,bool UDP);
	
	UFUNCTION(BlueprintCallable, Category = "UDP")
	bool UDP_SendString(FString ToSend);
	
};
