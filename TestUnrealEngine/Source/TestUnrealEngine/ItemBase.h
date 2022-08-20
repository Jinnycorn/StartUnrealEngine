// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class TESTUNREALENGINE_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AItemBase();

	UPROPERTY(VisibleAnywhere)
	class UWorld* World;



protected:
	virtual void BeginPlay() override;

	//virtual void PostInitializeComponents() override;

	//UFUNCTION()
	//void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



public:

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemKey; //아이템끼리의 구분 (Weapon, Potion)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemNo = 0; //아이템 내에서 구분(Weapon-1, Weapon-2)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDisplayName;

};
