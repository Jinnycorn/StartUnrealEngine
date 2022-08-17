// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyWeapon.generated.h"


UCLASS()
class TESTUNREALENGINE_API AMyWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyWeapon();

	//무기 잡는 함수 따로 빼줌
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AActor* OtherActor);

	UPROPERTY(VisibleAnywhere)
	class UWorld* World;

	AMyWeapon* SpawnedActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );
	
	UFUNCTION()
	void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:

	UPROPERTY(VisibleAnywhere)
	//UStaticMeshComponent* Weapon;
	USkeletalMeshComponent* Weapon;
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemKey; //아이템끼리의 구분 (Weapon, Potion)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemNo; //아이템 내에서 구분(Weapon-1, Weapon-2)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;

};
