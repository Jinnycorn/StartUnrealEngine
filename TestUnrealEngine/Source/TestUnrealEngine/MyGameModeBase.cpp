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
		//UE_LOG(LogTemp, Warning, TEXT("SpawnDataTable Succeed!"));
		SpawnDataTable = SPAWNDATA.Object;
	}

	//데이터테이블 내용들을 Map에 저장해주기 -> 에러 
	//MonsterMap.Add(GetSpawnData(1)->D_MonsterNo,SpawnDataTable[0]);
	//MonsterMap.Add(GetSpawnData(2)->D_MonsterNo, SpawnDataTable[1]);

	MonsterMap.Add(GetSpawnData(1)->D_MonsterNo);
	MonsterMap.Add(GetSpawnData(2)->D_MonsterNo);
	
	FMonsterSpawnData* Mon1 = MonsterMap.Find(1);
	Mon1->D_MonsterNo = GetSpawnData(1)->D_MonsterNo;
	Mon1->D_MonsterKey = GetSpawnData(1)->D_MonsterKey;	
	Mon1->D_SpawnPosition = GetSpawnData(1)->D_SpawnPosition;
	Mon1->D_RespawnTime = GetSpawnData(1)->D_RespawnTime;
	Mon1->D_DeadTime = GetSpawnData(1)->D_DeadTime;
	Mon1->D_isDead = GetSpawnData(1)->D_isDead;
	
	FMonsterSpawnData* Mon2 = MonsterMap.Find(2);
	Mon2->D_MonsterNo = GetSpawnData(2)->D_MonsterNo;
	Mon2->D_MonsterKey = GetSpawnData(2)->D_MonsterKey;
	Mon2->D_SpawnPosition = GetSpawnData(2)->D_SpawnPosition;
	Mon2->D_RespawnTime = GetSpawnData(2)->D_RespawnTime;
	Mon2->D_DeadTime = GetSpawnData(2)->D_DeadTime;
	Mon2->D_isDead = GetSpawnData(2)->D_isDead;
	
	/*UE_LOG(LogTemp, Warning, TEXT("FMonSpawnData is %f"), Mon2->D_DeadTime);
	if (Mon2->D_isDead)
	{
		UE_LOG(LogTemp, Warning, TEXT("true"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("false"))
	}
	UE_LOG(LogTemp, Warning, TEXT("Mon Location :: %s"), *(Mon2->D_SpawnPosition).ToString());*/

	//FMonsterSpawnData* Ptr7 = MonsterMap.Find(1);
	//UE_LOG(LogTemp, Warning, TEXT("FMonSpawnData is %s"), Ptr7);

	
	for (auto& i : MonsterMap)
	{
		//MonsterMap에 있는 데이터로 Monster Spawn 해주기
		//APawn* ResultPawn = SpawnActor<AMyMonster>(DefaultPawnClass, Mon1->D_SpawnPosition, StartRotation, NULL, Instigator);
		//GetWorld()->SpawnActor<AMyMonster>(AMyMonster::StaticClass(), Mon1->D_SpawnPosition);
	
	}


	
}

FMonsterSpawnData* AMyGameModeBase::GetSpawnData(int32 MonsterNo)
{

	return SpawnDataTable->FindRow<FMonsterSpawnData>(*FString::FromInt(MonsterNo), TEXT(""));

}

void AMyGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameTime += DeltaTime;
	//UE_LOG(LogTemp, Warning, TEXT("DT is  %f"),GameTime); //잘 찍힘 1,2초씩


}

