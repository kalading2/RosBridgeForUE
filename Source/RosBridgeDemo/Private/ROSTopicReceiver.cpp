// Fill out your copyright notice in the Description page of Project Settings.


#include "ROSTopicReceiver.h"

#include "ROSTime.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/PoseStamped.h"
#include "std_msgs/String.h"


// Sets default values
AROSTopicReceiver::AROSTopicReceiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// spCameraManager = NewObject<USPCameraManager>(this);
}

// Called when the game starts or when spawned
void AROSTopicReceiver::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AROSTopicReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Handler!=nullptr)
	{
		Handler->Process();
	}
}

void AROSTopicReceiver::RosConnect(FString ServerIP, int32 ServerPort, FString Trans_Topic, FString Pose_Topic, FString Twist_Topic,FString MsgType)
{
	//新建一个rosbridge
	Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(TCHAR_TO_UTF8(*ServerIP), ServerPort));
	//连接服务器
	Handler->Connect();
	
	// Add topic subscribers and publishers
	//新建Subscriber，并添加到Handler里
	mStringSubscriber = MakeShareable<ROSStringSubscriber>(new ROSStringSubscriber(TCHAR_TO_UTF8(*Trans_Topic)));
	Handler->AddSubscriber(mStringSubscriber);
	mPoseSubscriber = MakeShareable<ROSPoseSubscriber>(new ROSPoseSubscriber(TCHAR_TO_UTF8(*Pose_Topic)));
	Handler->AddSubscriber(mPoseSubscriber);
	mTwistSubscriber = MakeShareable<ROSTwistSubscriber>(new ROSTwistSubscriber(TCHAR_TO_UTF8(*Twist_Topic)));
	Handler->AddSubscriber(mTwistSubscriber);
	mStampSubscriber = MakeShareable<ROSStampSubscriber>(new ROSStampSubscriber(TCHAR_TO_UTF8(*MsgType)));
	Handler->AddSubscriber(mStampSubscriber);
	
	TransTopic = Trans_Topic;
	PoseTopic = Pose_Topic;
	TwistTopic = Twist_Topic;
	

	//新建publisher，并添加到Handler里
	// Publisher = MakeShareable<FROSBridgePublisher>(new FROSBridgePublisher(TCHAR_TO_UTF8(*TopicName), TCHAR_TO_UTF8(*MsgType)));
	// Handler->AddPublisher(Publisher);
	// MsgsType = MsgType;
}

void AROSTopicReceiver::AddRosPublish(FString TopicName, FString MsgType)
{
	Publisher = MakeShareable<FROSBridgePublisher>(new FROSBridgePublisher(TCHAR_TO_UTF8(*TopicName), TCHAR_TO_UTF8(*MsgType)));
	Handler->AddPublisher(Publisher);
	MsgsType = MsgType;
	
}



void AROSTopicReceiver::RosSendPoseMsg(FString TopicName, FMachineInfoStruct msg)
{
	//Publisher = MakeShareable<FROSBridgePublisher>(new FROSBridgePublisher(TCHAR_TO_UTF8(*TopicName), TEXT("std_msgs/String")));
	Publisher = MakeShareable<FROSBridgePublisher>(new FROSBridgePublisher(TCHAR_TO_UTF8(*TopicName), MsgsType));

	if(TopicName == "move_base_simple/goal")
	{
		geometry_msgs::PoseStamped PoseMsg;
		
		//填充PoseStamped头
		std_msgs::Header msg_h;
		msg_h.SetSeq(FCString::Atoi(*msg.seq));
		msg_h.SetStamp(FROSTime::Now());
		msg_h.SetFrameId(msg.frame_id);
		
		//填充PoseStamped位置
		geometry_msgs::Pose msg_pos;
		//pose包含point和quaternaion
		geometry_msgs::Point msg_point;
		msg_point.SetVector(FVector(FCString::Atoi(*msg.posx),FCString::Atoi(*msg.posy),FCString::Atoi(*msg.posZ)));
		msg_pos.SetPosition(msg_point);
		geometry_msgs::Quaternion msg_oreint;
		msg_oreint.SetQuat(FQuat(FCString::Atoi(*msg.orix),FCString::Atoi(*msg.oriy),FCString::Atoi(*msg.oriz),FCString::Atoi(*msg.oriw)));
		msg_pos.SetPosition(msg_point);
		msg_pos.SetOrientation(msg_oreint);
		PoseMsg.SetHeader(msg_h);
		PoseMsg.SetPose(msg_pos);
		
		TSharedPtr<geometry_msgs::PoseStamped> PosMsgPtr(new geometry_msgs::PoseStamped(PoseMsg));
		Handler->PublishMsg(TopicName, PosMsgPtr);
	}

}

void AROSTopicReceiver::RosSendTwishMsg(FString TopicName, FVector Vec1 , FVector Vec2)
{
	//Publisher = MakeShareable<FROSBridgePublisher>(new FROSBridgePublisher(TCHAR_TO_UTF8(*TopicName), TEXT("std_msgs/String")));
	Publisher = MakeShareable<FROSBridgePublisher>(new FROSBridgePublisher(TCHAR_TO_UTF8(*TopicName), MsgsType));
	
	if(TopicName == "mode"|TopicName == "cmd_vel")
	{
		geometry_msgs::Twist msg_twi;
		
		msg_twi.SetLinear(FVector(Vec1.X,Vec1.Y,Vec1.Z));
		msg_twi.SetAngular(FVector(Vec2.X,Vec2.Y,Vec2.Z));
		
		TSharedPtr<geometry_msgs::Twist> TwiMsgPtr(new geometry_msgs::Twist(msg_twi));
		Handler->PublishMsg(TopicName, TwiMsgPtr);
	}
	

}

void AROSTopicReceiver::RosSendStringMsg(FString TopicName,FString msg)
{
	Publisher = MakeShareable<FROSBridgePublisher>(new FROSBridgePublisher(TCHAR_TO_UTF8(*TopicName), TEXT("std_msgs/String")));

	if(TopicName == "poses")
	{
		std_msgs::String msg_poses;

		msg_poses.SetData(msg);
		
		TSharedPtr<std_msgs::String> PosMsgPtr(new std_msgs::String(msg_poses));
		
		Handler->PublishMsg(TopicName, PosMsgPtr);
		
	}
	
}

void AROSTopicReceiver::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(Handler!=nullptr)
	{
		Handler->Disconnect();
	}

	Super::EndPlay(EndPlayReason);
}
