// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class TESTUNREALENGINE_API UItem : public UObject
{
	GENERATED_BODY()
	
public:
	//UPROPERTY(VisibleAnywhere)
	//	string ItemName=""; //아이템 이름

	UPROPERTY()
		int32 ItemIndex = 0; //아이템 인덱스
	
	//UPROPERTY(VisibleAnywhere)
	//	string ItemDescription = 0; //아이템 설명

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Trigger;
};
