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

	//text for using the item (Equip, Eat, etc)

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText UseActionText;

	//Thumbnail
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item") ¿ø·¡²¨
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UPROPERTY(BlueprintReadWrite, Category = "Item")
	class UTexture2D* Thumbnail;

	//display name 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;

	//optional description for the item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int32 ItemKey;


	
	
};

