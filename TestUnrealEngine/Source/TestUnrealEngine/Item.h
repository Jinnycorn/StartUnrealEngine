// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced
 */
UCLASS( BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class TESTUNREALENGINE_API UItem : public UObject
{
	GENERATED_BODY()
	
public:
	UItem();
	

	virtual class UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
	class UWorld* World;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDisplayName;

    //The inventory that owns this item
	UPROPERTY()
	class UInventoryComponent* OwningInventory;

	virtual void Use(class AMyCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class AMyCharacter* Character);


};
