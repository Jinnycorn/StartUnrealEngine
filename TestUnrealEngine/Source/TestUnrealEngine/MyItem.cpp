// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItem.h"

// Sets default values
AMyItem::AMyItem()
{
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");

}

void AMyItem::Use(class AMyCharacter* Character)
{

}

