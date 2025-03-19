// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSPoseSubscriber.h"
#include <string>

#include "std_msgs/String.h"

#include "geometry_msgs/PoseWithCovarianceStamped.h"


ROSPoseSubscriber::ROSPoseSubscriber(const FString& InTopic) :
	FROSBridgeSubscriber(InTopic, TEXT("geometry_msgs/PoseWithCovarianceStamped"))
{

}

ROSPoseSubscriber::~ROSPoseSubscriber()
{
}

TSharedPtr<FROSBridgeMsg> ROSPoseSubscriber::ParseMessage(TSharedPtr<FJsonObject> JsonObject) const
{
	
	 TSharedPtr<geometry_msgs::PoseWithCovarianceStamped> PoseMessage = MakeShareable<geometry_msgs::PoseWithCovarianceStamped>(new geometry_msgs::PoseWithCovarianceStamped());
	 PoseMessage->FromJson(JsonObject);
	 return StaticCastSharedPtr<FROSBridgeMsg>(PoseMessage);
	
}

void ROSPoseSubscriber::Callback(TSharedPtr<FROSBridgeMsg> Msg)
{
	
	if (!Msg)
	{
		UE_LOG(LogTemp, Warning, TEXT("Message empty "));
		return;
	}
	
	TSharedPtr<geometry_msgs::PoseWithCovarianceStamped> PoseMessage = StaticCastSharedPtr<geometry_msgs::PoseWithCovarianceStamped>(Msg);
	seq = FString::FromInt(PoseMessage->GetHeader().GetSeq());
	//secs = FString::FromInt(PoseMessage->GetHeader().GetStamp().Secs());
	//nsecs = FString::FromInt(PoseMessage->GetHeader().GetStamp().NSecs());
	frame_id = PoseMessage->GetHeader().GetFrameId();
	posx = FString::SanitizeFloat(PoseMessage->GetPose().GetPose().GetPosition().GetX());
	posy = FString::SanitizeFloat(PoseMessage->GetPose().GetPose().GetPosition().GetY());
	posZ = FString::SanitizeFloat(PoseMessage->GetPose().GetPose().GetPosition().GetZ());
	orix = FString::SanitizeFloat(PoseMessage->GetPose().GetPose().GetOrientation().GetX());
	oriy = FString::SanitizeFloat(PoseMessage->GetPose().GetPose().GetOrientation().GetY());
	oriz = FString::SanitizeFloat(PoseMessage->GetPose().GetPose().GetOrientation().GetZ());
	oriw = FString::SanitizeFloat(PoseMessage->GetPose().GetPose().GetOrientation().GetW());
	
}
