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
	// Sets default values for this actor's properties
	AMyPotion();

	/*UPROPERTY(VisibleAnywhere)
	class UWorld* World;*/

	AMyPotion* SpawnedActor;
protected:
	
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Potion;

	/*UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemNo=0; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDisplayName;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;


};
