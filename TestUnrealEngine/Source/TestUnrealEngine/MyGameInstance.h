// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MyGameInstance.generated.h"

USTRUCT()
struct FMyCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;
};

USTRUCT(BlueprintType)
struct FMyMonsterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 D_MonsterKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 D_MonsterLevel;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 D_MonsterHp;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 D_MonsterAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 D_MonsterMaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 D_MonsterRewardItemKey;
};


USTRUCT(BlueprintType)
struct FMyItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText D_ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 D_ItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* D_Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText D_ItemDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 D_Health;




};


UCLASS()
class TESTUNREALENGINE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	virtual void Init() override;

	FMyCharacterData* GetStatData(int32 Level);

	//ItemData 가져오기
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* IDataTable;

	
	FMyItemData* GetItemData(int32 ItemKey);

	//MonsterData 가져오기
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* MDataTable;
	
	FMyMonsterData* GetMonsterData(int32 MonsterKey);

private:
	UPROPERTY()
	class UDataTable* MyStats;

	
};
