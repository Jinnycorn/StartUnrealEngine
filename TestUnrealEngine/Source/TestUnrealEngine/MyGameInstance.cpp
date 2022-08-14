// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DATA(TEXT("DataTable'/Game/Data/StatTable.StatTable'"));

	
		MyStats = DATA.Object;

	//DataTable √ ±‚»≠
	static ConstructorHelpers::FObjectFinder<UDataTable> ITEMDATA(TEXT("DataTable'/Game/Data/ItemTable.ItemTable'"));
	if (ITEMDATA.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		IDataTable = ITEMDATA.Object;
	}
	
}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance %d"),GetStatData(1)->Attack);
	//UE_LOG(LogTemp, Warning, TEXT("MyGameInstance %s"), GetItemData(0)->D_ItemDisplayName);
}

FMyCharacterData* UMyGameInstance::GetStatData(int32 Level)
{
	return MyStats->FindRow<FMyCharacterData>(*FString::FromInt(Level), TEXT(""));
}

FMyItemData* UMyGameInstance::GetItemData(int32 ItemKey)
{

	return IDataTable->FindRow<FMyItemData>(*FString::FromInt(ItemKey), TEXT(""));

}