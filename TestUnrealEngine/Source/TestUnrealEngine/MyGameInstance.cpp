// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> STATDATA(TEXT("DataTable'/Game/Data/StatTable.StatTable'"));

	
		MyStats = STATDATA.Object;

	//DataTable √ ±‚»≠
	static ConstructorHelpers::FObjectFinder<UDataTable> ITEMDATA(TEXT("DataTable'/Game/Data/ItemTable.ItemTable'"));
	if (ITEMDATA.Succeeded())
	{
		//UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		IDataTable = ITEMDATA.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> MONSTERDATA(TEXT("DataTable'/Game/Data/MonsterTable.MonsterTable'"));
	if (MONSTERDATA.Succeeded())
	{
		//UE_LOG(LogTemp, Warning, TEXT("MonsterTable Succeed!"));
		MDataTable = MONSTERDATA.Object;
	}

	
}

void UMyGameInstance::Init()
{
	Super::Init();
	//UE_LOG(LogTemp, Warning, TEXT("MyGameInstance %d"),GetStatData(1)->Attack);

}

FMyCharacterData* UMyGameInstance::GetStatData(int32 Level)
{
	return MyStats->FindRow<FMyCharacterData>(*FString::FromInt(Level), TEXT(""));
}

FMyItemData* UMyGameInstance::GetItemData(int32 ItemKey)
{

	return IDataTable->FindRow<FMyItemData>(*FString::FromInt(ItemKey), TEXT(""));

}

FMyMonsterData* UMyGameInstance::GetMonsterData(int32 MonsterKey)
{

	return MDataTable->FindRow<FMyMonsterData>(*FString::FromInt(MonsterKey), TEXT(""));

}