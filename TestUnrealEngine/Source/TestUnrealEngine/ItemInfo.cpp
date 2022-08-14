// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfo.h"


UItemInfo::UItemInfo()
{
	
	ItemDisplayName = FText::FromString("ItemInfo");
	
	ItemKey = 1;
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextureObj(TEXT("Texture2D'/Game/IMG/sword_IMG.sword_IMG'"));
		if (TextureObj.Succeeded())
			Thumbnail = TextureObj.Object;
	
	
}