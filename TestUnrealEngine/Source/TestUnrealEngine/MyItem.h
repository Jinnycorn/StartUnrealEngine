// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyItem.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable, DefaultToInstanced)
class TESTUNREALENGINE_API AMyItem : public AActor
{
	GENERATED_BODY()
	
public:
	AMyItem();

	virtual class UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
		class UWorld* World;
	//text for using the item (Equip, Eat, etc)

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText UseActionText;

	//Thumbnail
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
		class UTexture2D* Thumbnail;

	//display name 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText ItemDisplayName;

	//optional description for the item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;

	//The inventory that owns this item
	UPROPERTY()
		class UInventoryComponent* OwningInventory;

	virtual void Use(class AMyCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
		void OnUse(class AMyCharacter* Character);


};
