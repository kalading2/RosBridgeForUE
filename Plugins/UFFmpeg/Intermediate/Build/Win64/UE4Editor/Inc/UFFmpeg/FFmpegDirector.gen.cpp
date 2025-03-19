// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UFFmpeg/Public/FFmpegDirector.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFFmpegDirector() {}
// Cross Module References
	UFFMPEG_API UClass* Z_Construct_UClass_UFFmpegDirector_NoRegister();
	UFFMPEG_API UClass* Z_Construct_UClass_UFFmpegDirector();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_UFFmpeg();
	ENGINE_API UClass* Z_Construct_UClass_UWorld_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UFFmpegDirector::execInitialize_Director)
	{
		P_GET_OBJECT(UWorld,Z_Param_World);
		P_GET_PROPERTY(FStrProperty,Z_Param_OutFileName);
		P_GET_UBOOL(Z_Param_UseGPU);
		P_GET_PROPERTY(FStrProperty,Z_Param_VideoFilter);
		P_GET_PROPERTY(FIntProperty,Z_Param_VideoFps);
		P_GET_PROPERTY(FIntProperty,Z_Param_VideoBitRate);
		P_GET_PROPERTY(FFloatProperty,Z_Param_AudioDelay);
		P_GET_PROPERTY(FFloatProperty,Z_Param_SoundVolume);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Initialize_Director(Z_Param_World,Z_Param_OutFileName,Z_Param_UseGPU,Z_Param_VideoFilter,Z_Param_VideoFps,Z_Param_VideoBitRate,Z_Param_AudioDelay,Z_Param_SoundVolume);
		P_NATIVE_END;
	}
	void UFFmpegDirector::StaticRegisterNativesUFFmpegDirector()
	{
		UClass* Class = UFFmpegDirector::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Initialize_Director", &UFFmpegDirector::execInitialize_Director },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics
	{
		struct FFmpegDirector_eventInitialize_Director_Parms
		{
			UWorld* World;
			FString OutFileName;
			bool UseGPU;
			FString VideoFilter;
			int32 VideoFps;
			int32 VideoBitRate;
			float AudioDelay;
			float SoundVolume;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_World;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_OutFileName;
		static void NewProp_UseGPU_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_UseGPU;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_VideoFilter;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_VideoFps;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_VideoBitRate;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_AudioDelay;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_SoundVolume;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_World = { "World", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegDirector_eventInitialize_Director_Parms, World), Z_Construct_UClass_UWorld_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_OutFileName = { "OutFileName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegDirector_eventInitialize_Director_Parms, OutFileName), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_UseGPU_SetBit(void* Obj)
	{
		((FFmpegDirector_eventInitialize_Director_Parms*)Obj)->UseGPU = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_UseGPU = { "UseGPU", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFmpegDirector_eventInitialize_Director_Parms), &Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_UseGPU_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_VideoFilter = { "VideoFilter", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegDirector_eventInitialize_Director_Parms, VideoFilter), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_VideoFps = { "VideoFps", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegDirector_eventInitialize_Director_Parms, VideoFps), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_VideoBitRate = { "VideoBitRate", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegDirector_eventInitialize_Director_Parms, VideoBitRate), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_AudioDelay = { "AudioDelay", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegDirector_eventInitialize_Director_Parms, AudioDelay), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_SoundVolume = { "SoundVolume", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegDirector_eventInitialize_Director_Parms, SoundVolume), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_World,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_OutFileName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_UseGPU,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_VideoFilter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_VideoFps,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_VideoBitRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_AudioDelay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::NewProp_SoundVolume,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/FFmpegDirector.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFFmpegDirector, nullptr, "Initialize_Director", nullptr, nullptr, sizeof(FFmpegDirector_eventInitialize_Director_Parms), Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFFmpegDirector_Initialize_Director()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFFmpegDirector_Initialize_Director_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UFFmpegDirector_NoRegister()
	{
		return UFFmpegDirector::StaticClass();
	}
	struct Z_Construct_UClass_UFFmpegDirector_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFFmpegDirector_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_UFFmpeg,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFFmpegDirector_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFFmpegDirector_Initialize_Director, "Initialize_Director" }, // 3892832338
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFFmpegDirector_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "FFmpegDirector.h" },
		{ "ModuleRelativePath", "Public/FFmpegDirector.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFFmpegDirector_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFFmpegDirector>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFFmpegDirector_Statics::ClassParams = {
		&UFFmpegDirector::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UFFmpegDirector_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFFmpegDirector_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFFmpegDirector()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFFmpegDirector_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFFmpegDirector, 3483729022);
	template<> UFFMPEG_API UClass* StaticClass<UFFmpegDirector>()
	{
		return UFFmpegDirector::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFFmpegDirector(Z_Construct_UClass_UFFmpegDirector, &UFFmpegDirector::StaticClass, TEXT("/Script/UFFmpeg"), TEXT("UFFmpegDirector"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFFmpegDirector);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
