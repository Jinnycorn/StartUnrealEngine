// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.h"
#include "MyPotion.generated.h"

UCLASS()
class TESTUNREALENGINE_API AMyPotion : public AItemBase
{
	GENERATED_BODY()
	
public:	

	AMyPotion();


	AMyPotion* SpawnedActor;

	void ReadItemPath();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Potion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString m_ItemPath;


protected:
	
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;



};
