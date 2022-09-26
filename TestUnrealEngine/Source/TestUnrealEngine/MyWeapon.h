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

	AMyWeapon();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AActor* OtherActor);

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Weapon;
	
	AMyWeapon* SpawnedActor;

protected:

	virtual void BeginPlay() override;
	
	virtual void PostInitializeComponents() override;



	
};
