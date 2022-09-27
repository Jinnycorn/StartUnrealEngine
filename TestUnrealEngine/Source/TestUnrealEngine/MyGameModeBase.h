// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MyGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FMonsterSpawnData: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 D_MonsterNo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 D_MonsterKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector D_SpawnPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float D_RespawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float D_DeadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool D_isDead;


};

UCLASS()
class TESTUNREALENGINE_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AMyGameModeBase();

	virtual void InitGame(const FString & MapName,
						const FString & Options,
						FString & ErrorMessage) override;

	virtual void Tick(float DeltaTime) override;
	
	TMap<int32, FMonsterSpawnData> MonsterMap;

public:
	
	
	TMap<int32, FMonsterSpawnData>& getMonsterMap() { return MonsterMap; }
	
	int32 m_GM_MonsterNo;
	float m_GameTime = 0.f;

	void SpawnMonster();

	FMonsterSpawnData* GetSpawnData(int32 MonsterNo);
	FMonsterSpawnData* Mon1;
	FMonsterSpawnData* Mon2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* SpawnDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_GM_ItemNo;

};
