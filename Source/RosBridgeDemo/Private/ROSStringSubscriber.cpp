// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSStringSubscriber.h"
#include <string>

#include "std_msgs/String.h"
#include "std_msgs/Int32.h"


ROSStringSubscriber::ROSStringSubscriber(const FString& InTopic) :
	//FROSBridgeSubscriber(InTopic, TEXT("geometry_msgs/PoseWithCovarianceStamped"))
	FROSBridgeSubscriber(InTopic, TEXT("std_msgs/Int32"))
{

}

ROSStringSubscriber::~ROSStringSubscriber()
{
}

TSharedPtr<FROSBridgeMsg> ROSStringSubscriber::ParseMessage(TSharedPtr<FJsonObject> JsonObject) const
{
	
	 TSharedPtr<std_msgs::String> StringMessage = MakeShareable<std_msgs::String>(new std_msgs::String());
	
	 //TSharedPtr<geometry_msgs::PoseWithCovarianceStamped> StringMessage = MakeShareable<geometry_msgs::PoseWithCovarianceStamped>(new geometry_msgs::PoseWithCovarianceStamped());
	 StringMessage->FromJson(JsonObject);
	 return StaticCastSharedPtr<FROSBridgeMsg>(StringMessage);

	 // TSharedPtr<std_msgs::Int32> StringMessage = MakeShareable<std_msgs::Int32>(new std_msgs::Int32);
	 // StringMessage->FromJson(JsonObject);
	 // return StaticCastSharedPtr<FROSBridgeMsg>(StringMessage);
	 
}

void ROSStringSubscriber::Callback(TSharedPtr<FROSBridgeMsg> Msg)
{
	
	if (!Msg)
	{
		UE_LOG(LogTemp, Warning, TEXT("Message empty "));
		return;
	}
	TSharedPtr<std_msgs::String> StringMessage = StaticCastSharedPtr<std_msgs::String>(Msg);
	 UE_LOG(LogTemp, Warning, TEXT("Message received! Content:%s"), *StringMessage->GetData());
	rosMsg = *StringMessage->GetData();
	
	//TSharedPtr<geometry_msgs::PoseWithCovarianceStamped> StringMessage = StaticCastSharedPtr<geometry_msgs::PoseWithCovarianceStamped>(Msg);
	//rosMsg = FString::FromInt(StringMessage->GetHeader().GetSeq());
	//rosMsg = StringMessage->GetHeader().GetFrameId();
	
	//TSharedPtr<std_msgs::Int32> IntMessage = StaticCastSharedPtr<std_msgs::Int32>(Msg);
	//RosMsg1 = IntMessage->GetData();
	return;
	
}
