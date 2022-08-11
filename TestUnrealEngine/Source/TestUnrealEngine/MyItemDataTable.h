// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "MyItemDataTable.generated.h"
USTRUCT(BlueprintType)
struct FMyItemDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 D_ItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* D_Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText D_ItemDisplayName;



};


class TESTUNREALENGINE_API MyItemDataTable
{
public:
	MyItemDataTable();
	~MyItemDataTable();
};
