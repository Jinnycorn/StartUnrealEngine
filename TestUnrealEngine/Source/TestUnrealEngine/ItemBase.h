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

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_ItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_ItemNo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* m_Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText m_ItemDisplayName;

	FString itemlist[100];



protected:
	virtual void BeginPlay() override;


	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	

};
