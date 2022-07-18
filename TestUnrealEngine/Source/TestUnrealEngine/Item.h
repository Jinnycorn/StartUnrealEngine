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
	//	string ItemName=""; //������ �̸�

	UPROPERTY()
		int32 ItemIndex = 0; //������ �ε���
	
	//UPROPERTY(VisibleAnywhere)
	//	string ItemDescription = 0; //������ ����

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Trigger;
};
