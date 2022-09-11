// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.h"
#include "MyWeapon.generated.h"


UCLASS()
class TESTUNREALENGINE_API AMyWeapon : public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyWeapon();

	//¹«±â Àâ´Â ÇÔ¼ö µû·Î »©ÁÜ
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AActor* OtherActor);

	//UPROPERTY(VisibleAnywhere)
	//class UWorld* World;

	AMyWeapon* SpawnedActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	virtual void PostInitializeComponents() override;

public:

	UPROPERTY(VisibleAnywhere)
	//UStaticMeshComponent* Weapon;
	USkeletalMeshComponent* Weapon;
	
	

};
