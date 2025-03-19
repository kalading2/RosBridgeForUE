// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UFFmpeg/Public/FFmpegFunctionLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFFmpegFunctionLibrary() {}
// Cross Module References
	UFFMPEG_API UClass* Z_Construct_UClass_UFFmpegFunctionLibrary_NoRegister();
	UFFMPEG_API UClass* Z_Construct_UClass_UFFmpegFunctionLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_UFFmpeg();
	ENGINE_API UClass* Z_Construct_UClass_UWorld_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UFFmpegFunctionLibrary::execGetWorldContext)
	{
		P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UWorld**)Z_Param__Result=UFFmpegFunctionLibrary::GetWorldContext(Z_Param_WorldContextObject);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UFFmpegFunctionLibrary::execCreateFFmpegDirector)
	{
		P_GET_OBJECT(UWorld,Z_Param_World);
		P_GET_PROPERTY(FStrProperty,Z_Param_OutFileName);
		P_GET_PROPERTY(FStrProperty,Z_Param_VideoFilter);
		P_GET_UBOOL(Z_Param_UseGPU);
		P_GET_PROPERTY(FIntProperty,Z_Param_FPS);
		P_GET_PROPERTY(FIntProperty,Z_Param_VideoBitRate);
		P_GET_PROPERTY(FFloatProperty,Z_Param_AudioDelay);
		P_GET_PROPERTY(FFloatProperty,Z_Param_SoundVolume);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UFFmpegFunctionLibrary::CreateFFmpegDirector(Z_Param_World,Z_Param_OutFileName,Z_Param_VideoFilter,Z_Param_UseGPU,Z_Param_FPS,Z_Param_VideoBitRate,Z_Param_AudioDelay,Z_Param_SoundVolume);
		P_NATIVE_END;
	}
	void UFFmpegFunctionLibrary::StaticRegisterNativesUFFmpegFunctionLibrary()
	{
		UClass* Class = UFFmpegFunctionLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateFFmpegDirector", &UFFmpegFunctionLibrary::execCreateFFmpegDirector },
			{ "GetWorldContext", &UFFmpegFunctionLibrary::execGetWorldContext },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics
	{
		struct FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms
		{
			UWorld* World;
			FString OutFileName;
			FString VideoFilter;
			bool UseGPU;
			int32 FPS;
			int32 VideoBitRate;
			float AudioDelay;
			float SoundVolume;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_World;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_OutFileName;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_VideoFilter;
		static void NewProp_UseGPU_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_UseGPU;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_FPS;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_VideoBitRate;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_AudioDelay;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_SoundVolume;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_World = { "World", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms, World), Z_Construct_UClass_UWorld_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_OutFileName = { "OutFileName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms, OutFileName), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_VideoFilter = { "VideoFilter", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms, VideoFilter), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_UseGPU_SetBit(void* Obj)
	{
		((FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms*)Obj)->UseGPU = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_UseGPU = { "UseGPU", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms), &Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_UseGPU_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_FPS = { "FPS", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms, FPS), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_VideoBitRate = { "VideoBitRate", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms, VideoBitRate), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_AudioDelay = { "AudioDelay", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms, AudioDelay), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_SoundVolume = { "SoundVolume", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms, SoundVolume), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_World,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_OutFileName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_VideoFilter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_UseGPU,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_FPS,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_VideoBitRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_AudioDelay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_SoundVolume,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/FFmpegFunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFFmpegFunctionLibrary, nullptr, "CreateFFmpegDirector", nullptr, nullptr, sizeof(FFmpegFunctionLibrary_eventCreateFFmpegDirector_Parms), Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics
	{
		struct FFmpegFunctionLibrary_eventGetWorldContext_Parms
		{
			UObject* WorldContextObject;
			UWorld* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegFunctionLibrary_eventGetWorldContext_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FFmpegFunctionLibrary_eventGetWorldContext_Parms, ReturnValue), Z_Construct_UClass_UWorld_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::NewProp_WorldContextObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/FFmpegFunctionLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UFFmpegFunctionLibrary, nullptr, "GetWorldContext", nullptr, nullptr, sizeof(FFmpegFunctionLibrary_eventGetWorldContext_Parms), Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UFFmpegFunctionLibrary_NoRegister()
	{
		return UFFmpegFunctionLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UFFmpegFunctionLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UFFmpegFunctionLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_UFFmpeg,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UFFmpegFunctionLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UFFmpegFunctionLibrary_CreateFFmpegDirector, "CreateFFmpegDirector" }, // 3563897845
		{ &Z_Construct_UFunction_UFFmpegFunctionLibrary_GetWorldContext, "GetWorldContext" }, // 1025492587
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UFFmpegFunctionLibrary_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "FFmpegFunctionLibrary.h" },
		{ "ModuleRelativePath", "Public/FFmpegFunctionLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UFFmpegFunctionLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFFmpegFunctionLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UFFmpegFunctionLibrary_Statics::ClassParams = {
		&UFFmpegFunctionLibrary::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UFFmpegFunctionLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UFFmpegFunctionLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UFFmpegFunctionLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UFFmpegFunctionLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UFFmpegFunctionLibrary, 2251450133);
	template<> UFFMPEG_API UClass* StaticClass<UFFmpegFunctionLibrary>()
	{
		return UFFmpegFunctionLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UFFmpegFunctionLibrary(Z_Construct_UClass_UFFmpegFunctionLibrary, &UFFmpegFunctionLibrary::StaticClass, TEXT("/Script/UFFmpeg"), TEXT("UFFmpegFunctionLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UFFmpegFunctionLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
