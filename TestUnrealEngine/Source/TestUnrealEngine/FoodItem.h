// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "FoodItem.generated.h"

/**
 * 
 */
UCLASS()
class TESTUNREALENGINE_API UFoodItem : public UItem
{
	GENERATED_BODY()
	
protected:

	virtual void Use(class AMyCharacter* Character) override;

};
