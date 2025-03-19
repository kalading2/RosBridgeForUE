// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <ROSBridgeHandler.h>

#include "ROSPoseSubscriber.h"
//#include "SPCameraManager.h"
#include "ROSStampSubscriber.h"
#include "ROSStringSubscriber.h"
#include "ROSTwistSubscriber.h"
#include "GameFramework/Actor.h"

#include "ROSTopicReceiver.generated.h"


USTRUCT(BlueprintType)
struct FMachineInfoStruct
{
	GENERATED_USTRUCT_BODY()

public:
	//是否到达目标点
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Goal = "";
	//机器人信息
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString seq = "";
	// UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// FString secs = "";
	// UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// FString nsecs = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString frame_id = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString posx = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString posy = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString posZ = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString orix = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString oriy = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString oriz = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString oriw = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString l1 = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString l2 = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString l3 = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString v1 = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString v2 = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString v3 = "";
	
};




UCLASS()
class ROSBRIDGEDEMO_API AROSTopicReceiver : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	
	AROSTopicReceiver();
	
	TSharedPtr<FROSBridgeHandler>Handler;
	TSharedPtr<ROSStringSubscriber> mStringSubscriber;
	TSharedPtr<ROSPoseSubscriber> mPoseSubscriber;
	TSharedPtr<ROSTwistSubscriber> mTwistSubscriber;
	TSharedPtr<ROSStampSubscriber> mStampSubscriber;
	TSharedPtr<FROSBridgePublisher> Publisher; // This
	
	
	
	// USPCameraManager *spCameraManager;
	FString TransTopic;
	FString PoseTopic;
	FString TwistTopic;
	
	FString MsgsType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "ROSServerInfo")
	void RosConnect(FString ServerIP,int32 ServerPort,FString Trans_Topic, FString Pose_Topic,  FString Twist_Topic,FString MsgType);
	UFUNCTION(BlueprintCallable, Category = "ROSServerInfo")
	void RosSendPoseMsg(FString TopicName,FMachineInfoStruct msg);
	UFUNCTION(BlueprintCallable, Category = "ROSServerInfo")
	void RosSendTwishMsg(FString TopicName,FVector Vec1 , FVector Vec2);
	UFUNCTION(BlueprintCallable, Category = "ROSServerInfo")
	void RosSendStringMsg(FString TopicName,FString PointString);
	
	UFUNCTION(BlueprintCallable, Category = "ROSServerInfo")
	void AddRosPublish(FString TopicName, FString MsgType);

	
	UFUNCTION(BlueprintCallable, Category = "ROSServerInfo")
	FMachineInfoStruct GetRosMsg(){
		FMachineInfoStruct machineInfoStruct;
		machineInfoStruct.Goal = mStringSubscriber->rosMsg;
		machineInfoStruct.seq = mPoseSubscriber->seq;
		//machineInfoStruct.secs = mPoseSubscriber->secs;
		//machineInfoStruct.nsecs = mPoseSubscriber->nsecs;
		machineInfoStruct.frame_id = mStampSubscriber->frame_id;
		machineInfoStruct.posx = mStampSubscriber->posx;
		machineInfoStruct.posy = mStampSubscriber->posy;
		machineInfoStruct.posZ = mStampSubscriber->posZ;
		machineInfoStruct.orix = mStampSubscriber->orix;
		machineInfoStruct.oriy = mStampSubscriber->oriy;
		machineInfoStruct.oriz = mStampSubscriber->oriz;
		machineInfoStruct.oriw = mStampSubscriber->oriw;
		machineInfoStruct.l1 = mTwistSubscriber->l1;
		machineInfoStruct.l2 = mTwistSubscriber->l2;
		machineInfoStruct.l3 = mTwistSubscriber->l3;
		machineInfoStruct.v1 = mTwistSubscriber->v1;
		machineInfoStruct.v2 = mTwistSubscriber->v2;
		machineInfoStruct.v3 = mTwistSubscriber->v3;
		
		return FMachineInfoStruct(machineInfoStruct);
		//return FMachineInfoStruct->rosMsg;
	}
	
};
