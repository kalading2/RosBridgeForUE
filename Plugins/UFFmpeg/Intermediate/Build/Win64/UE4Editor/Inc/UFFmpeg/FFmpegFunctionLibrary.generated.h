// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
class UWorld;
#ifdef UFFMPEG_FFmpegFunctionLibrary_generated_h
#error "FFmpegFunctionLibrary.generated.h already included, missing '#pragma once' in FFmpegFunctionLibrary.h"
#endif
#define UFFMPEG_FFmpegFunctionLibrary_generated_h

#define RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_SPARSE_DATA
#define RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetWorldContext); \
	DECLARE_FUNCTION(execCreateFFmpegDirector);


#define RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetWorldContext); \
	DECLARE_FUNCTION(execCreateFFmpegDirector);


#define RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUFFmpegFunctionLibrary(); \
	friend struct Z_Construct_UClass_UFFmpegFunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(UFFmpegFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/UFFmpeg"), NO_API) \
	DECLARE_SERIALIZER(UFFmpegFunctionLibrary)


#define RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_INCLASS \
private: \
	static void StaticRegisterNativesUFFmpegFunctionLibrary(); \
	friend struct Z_Construct_UClass_UFFmpegFunctionLibrary_Statics; \
public: \
	DECLARE_CLASS(UFFmpegFunctionLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/UFFmpeg"), NO_API) \
	DECLARE_SERIALIZER(UFFmpegFunctionLibrary)


#define RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UFFmpegFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFFmpegFunctionLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFFmpegFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFFmpegFunctionLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFFmpegFunctionLibrary(UFFmpegFunctionLibrary&&); \
	NO_API UFFmpegFunctionLibrary(const UFFmpegFunctionLibrary&); \
public:


#define RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UFFmpegFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UFFmpegFunctionLibrary(UFFmpegFunctionLibrary&&); \
	NO_API UFFmpegFunctionLibrary(const UFFmpegFunctionLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UFFmpegFunctionLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UFFmpegFunctionLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UFFmpegFunctionLibrary)


#define RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_PRIVATE_PROPERTY_OFFSET
#define RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_15_PROLOG
#define RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_PRIVATE_PROPERTY_OFFSET \
	RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_SPARSE_DATA \
	RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_RPC_WRAPPERS \
	RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_INCLASS \
	RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_PRIVATE_PROPERTY_OFFSET \
	RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_SPARSE_DATA \
	RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_INCLASS_NO_PURE_DECLS \
	RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> UFFMPEG_API UClass* StaticClass<class UFFmpegFunctionLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID RosBridgeDemo_Plugins_UFFmpeg_Source_UFFmpeg_Public_FFmpegFunctionLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
