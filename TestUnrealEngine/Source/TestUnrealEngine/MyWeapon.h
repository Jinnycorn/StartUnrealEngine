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

	//¹«±â Àâ´Â ÇÔ¼ö µû·Î »©ÁÜ
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

	

	//Thumbnail
	UPROPERTY(BlueprintReadWrite, Category = "Item")
	class UTexture2D* Thumbnail;


	//display name 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* IDataTable;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FName RandomName;
};
