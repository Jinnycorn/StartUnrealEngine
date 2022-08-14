// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInfo.generated.h"


UCLASS()
class TESTUNREALENGINE_API UItemInfo : public UObject
{
	GENERATED_BODY()


public:
	UItemInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDisplayName;


	
	
};

