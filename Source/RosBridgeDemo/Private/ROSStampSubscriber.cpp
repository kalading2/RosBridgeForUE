// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSStampSubscriber.h"
#include <string>

#include "std_msgs/String.h"

#include "geometry_msgs/PoseStamped.h"


ROSStampSubscriber::ROSStampSubscriber(const FString& InTopic) :
	FROSBridgeSubscriber(InTopic, TEXT("geometry_msgs/PoseStamped"))
{

}

ROSStampSubscriber::~ROSStampSubscriber()
{
}

TSharedPtr<FROSBridgeMsg> ROSStampSubscriber::ParseMessage(TSharedPtr<FJsonObject> JsonObject) const
{
	
	 TSharedPtr<geometry_msgs::PoseStamped> PoseMessage = MakeShareable<geometry_msgs::PoseStamped>(new geometry_msgs::PoseStamped());
	 PoseMessage->FromJson(JsonObject);
	 return StaticCastSharedPtr<FROSBridgeMsg>(PoseMessage);
	
}

void ROSStampSubscriber::Callback(TSharedPtr<FROSBridgeMsg> Msg)
{
	
	if (!Msg)
	{
		UE_LOG(LogTemp, Warning, TEXT("Message empty "));
		return;
	}
	
	TSharedPtr<geometry_msgs::PoseStamped> PoseMessage = StaticCastSharedPtr<geometry_msgs::PoseStamped>(Msg);
	seq = FString::FromInt(PoseMessage->GetHeader().GetSeq());
	//secs = FString::FromInt(PoseMessage->GetHeader().GetStamp().Secs());
	//nsecs = FString::FromInt(PoseMessage->GetHeader().GetStamp().NSecs());
	frame_id = PoseMessage->GetHeader().GetFrameId();
	posx = FString::SanitizeFloat(PoseMessage->GetPose().GetPosition().GetX());
	posy = FString::SanitizeFloat(PoseMessage->GetPose().GetPosition().GetY());
	posZ = FString::SanitizeFloat(PoseMessage->GetPose().GetPosition().GetZ());
	orix = FString::SanitizeFloat(PoseMessage->GetPose().GetOrientation().GetX());
	oriy = FString::SanitizeFloat(PoseMessage->GetPose().GetOrientation().GetY());
	oriz = FString::SanitizeFloat(PoseMessage->GetPose().GetOrientation().GetZ());
	oriw = FString::SanitizeFloat(PoseMessage->GetPose().GetOrientation().GetW());
	
}
