// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfo.h"


UItemInfo::UItemInfo()
{
	ItemDisplayName = FText::FromString("ItemInfo");
	UseActionText = FText::FromString("Use");
	
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextureObj(TEXT("Texture2D'/Game/IMG/sword_IMG.sword_IMG'"));
		if (TextureObj.Succeeded())
			Thumbnail = TextureObj.Object;
	
	
}