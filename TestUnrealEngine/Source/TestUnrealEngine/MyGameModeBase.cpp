// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"
#include "MyMonster.h"


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
		SpawnDataTable = SPAWNDATA.Object;
	}



	MonsterMap.Add(GetSpawnData(1)->D_MonsterNo);
	MonsterMap.Add(GetSpawnData(2)->D_MonsterNo);
	
	Mon1 = MonsterMap.Find(1);

	Mon1->D_MonsterNo = GetSpawnData(1)->D_MonsterNo;
	Mon1->D_MonsterKey = GetSpawnData(1)->D_MonsterKey;	
	Mon1->D_SpawnPosition = GetSpawnData(1)->D_SpawnPosition;
	Mon1->D_RespawnTime = GetSpawnData(1)->D_RespawnTime;
	Mon1->D_DeadTime = GetSpawnData(1)->D_DeadTime;
	Mon1->D_isDead = GetSpawnData(1)->D_isDead;
	

	Mon2 = MonsterMap.Find(2);

	Mon2->D_MonsterNo = GetSpawnData(2)->D_MonsterNo;
	Mon2->D_MonsterKey = GetSpawnData(2)->D_MonsterKey;
	Mon2->D_SpawnPosition = GetSpawnData(2)->D_SpawnPosition;
	Mon2->D_RespawnTime = GetSpawnData(2)->D_RespawnTime;
	Mon2->D_DeadTime = GetSpawnData(2)->D_DeadTime;
	Mon2->D_isDead = GetSpawnData(2)->D_isDead;
	


	//FMonsterSpawnData* Ptr7 = MonsterMap.Find(1);
	//UE_LOG(LogTemp, Warning, TEXT("FMonSpawnData is %s"), Ptr7);

}

FMonsterSpawnData* AMyGameModeBase::GetSpawnData(int32 MonsterNo)
{

	return SpawnDataTable->FindRow<FMonsterSpawnData>(*FString::FromInt(MonsterNo), TEXT(""));

}

void AMyGameModeBase::InitGame(const FString& MapName, const FString& Options,FString& ErrorMessage)
{
	Super::InitGame(MapName,Options,ErrorMessage);

	for (auto& i : MonsterMap)
	{
		//MonsterMap에 있는 데이터로 Monster Spawn 해주기
		FActorSpawnParameters SpawnParams;
		FRotator rotator;

		UWorld* world = GetWorld();
		if (world == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Getworld is null"));
		}
	
		

		AMyMonster* MyMonster;
		MyMonster = GetWorld()->SpawnActor<AMyMonster>(AMyMonster::StaticClass(), i.Value.D_SpawnPosition, rotator, SpawnParams);
		
		MyMonster->MonsterNo = i.Key;
		UE_LOG(LogTemp, Warning, TEXT("SpawnMons's MonsterNo: %d "), MyMonster->MonsterNo);
		//UE_LOG(LogTemp, Warning, TEXT("M1 Spawn pos: %s "), *(i.Value.D_SpawnPosition).ToString());
		//UE_LOG(LogTemp, Warning, TEXT("M1 Spawn pos: %s "), *(MonsterMap[1].D_SpawnPosition).ToString());
		
		//GetWorld()->SpawnActor<AMyMonster>(AMyMonster::StaticClass(), Mon2->D_SpawnPosition, rotator, SpawnParams);
		//UE_LOG(LogTemp, Warning, TEXT("M2 Spawn pos: %s "), *(Mon2->D_SpawnPosition).ToString());
	
		
		
	
	}
}

void AMyGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameTime += DeltaTime;
	//UE_LOG(LogTemp, Warning, TEXT("DT is  %f"),GameTime); //잘 찍힘 1,2초씩



}
