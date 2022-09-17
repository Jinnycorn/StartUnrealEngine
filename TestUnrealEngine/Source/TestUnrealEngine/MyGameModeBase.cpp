// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"


AMyGameModeBase::AMyGameModeBase()
{

	PrimaryActorTick.bCanEverTick = true;
	//코드로 할 때
	//DefaultPawnClass = AMyCharacter::StaticClass();
	
	//블루 프린트로 바꾸기
	static ConstructorHelpers::FClassFinder<ACharacter>BP_Char(TEXT("Blueprint'/Game/Blueprints/BP_MyCharacter.BP_MyCharacter_C'"));

	if (BP_Char.Succeeded())
	{
		DefaultPawnClass = BP_Char.Class;
	}

	
	GM_ItemNo = 0;

	//몬스터 스폰 테이블의 정보를 몬스터 맵에 넣어주기
	
	//MonsterSpawnTable 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> SPAWNDATA(TEXT("DataTable'/Game/Data/MonsterSpawnTable.MonsterSpawnTable'"));
	if (SPAWNDATA.Succeeded())
	{
		//UE_LOG(LogTemp, Warning, TEXT("SpawnDataTable Succeed!"));
		SpawnDataTable = SPAWNDATA.Object;
	}

	//데이터테이블의 monsterNo
	//MonsterMap.Emplace();
	
}

//FMonsterSpawnData* AMyGameModeBase::GetSpawnData(int32 MonsterNo)
//{
//
//	//return SpawnDataTable->FindRow<FMonsterSpawnData>(*FString::FromInt(ItemKey), TEXT(""));
//
//}

void AMyGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameTime += DeltaTime;
	//UE_LOG(LogTemp, Warning, TEXT("DT is  %f"),GameTime); //잘 찍힘 1,2초씩


}

