// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSTwistSubscriber.h"
#include <string>
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"

ROSTwistSubscriber::ROSTwistSubscriber(const FString& InTopic) :
	FROSBridgeSubscriber(InTopic, TEXT("geometry_msgs/Twist"))
{

}

ROSTwistSubscriber::~ROSTwistSubscriber()
{
}

TSharedPtr<FROSBridgeMsg> ROSTwistSubscriber::ParseMessage(TSharedPtr<FJsonObject> JsonObject) const
{
	
	 TSharedPtr<geometry_msgs::Twist> TwistMessage = MakeShareable<geometry_msgs::Twist>(new geometry_msgs::Twist());
	 TwistMessage->FromJson(JsonObject);
	 return StaticCastSharedPtr<FROSBridgeMsg>(TwistMessage);
	
	 
}

void ROSTwistSubscriber::Callback(TSharedPtr<FROSBridgeMsg> Msg)
{
	
	if (!Msg)
	{
		UE_LOG(LogTemp, Warning, TEXT("Message empty "));
		return;
	}
	
	TSharedPtr<geometry_msgs::Twist> TwistMessage = StaticCastSharedPtr<geometry_msgs::Twist>(Msg);
	l1 = FString::FromInt(TwistMessage->GetLinear().GetX());
	l2 = FString::FromInt(TwistMessage->GetLinear().GetY());
	l3 = FString::FromInt(TwistMessage->GetLinear().GetZ());
	v1 = FString::FromInt(TwistMessage->GetAngular().GetX());
	v2 = FString::FromInt(TwistMessage->GetAngular().GetY());
	v3 = FString::FromInt(TwistMessage->GetAngular().GetZ());
	
	
}
