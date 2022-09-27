// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"
#include "MyMonster.h"


AMyGameModeBase::AMyGameModeBase()
{

	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<ACharacter>BP_Char(TEXT("Blueprint'/Game/Blueprints/BP_MyCharacter.BP_MyCharacter_C'"));

	if (BP_Char.Succeeded())
	{
		DefaultPawnClass = BP_Char.Class;
	}

	
	m_GM_ItemNo = 0;

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

}

FMonsterSpawnData* AMyGameModeBase::GetSpawnData(int32 MonsterNo)
{

	return SpawnDataTable->FindRow<FMonsterSpawnData>(*FString::FromInt(MonsterNo), TEXT(""));

}

void AMyGameModeBase::InitGame(const FString& MapName, const FString& Options,FString& ErrorMessage)
{
	Super::InitGame(MapName,Options,ErrorMessage);
	SpawnMonster();

}

void AMyGameModeBase::SpawnMonster()
{
	for (auto& i : MonsterMap)
	{
		FActorSpawnParameters spawnParams;
		FRotator rotator;

		UWorld* world = GetWorld();
		if (world == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Getworld is null"));
		}

		i.Value.D_isDead = false;


		AMyMonster* myMonster;
		myMonster = world->SpawnActor<AMyMonster>(AMyMonster::StaticClass(), i.Value.D_SpawnPosition, rotator, spawnParams);

		myMonster->m_MonsterNo = i.Key;




	}
}

void AMyGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_GameTime += DeltaTime;


	for (auto& i : MonsterMap)
	{

		if ((i.Value.D_isDead))
		{
			
			if (m_GameTime >= i.Value.D_DeadTime + i.Value.D_RespawnTime)
			{
		
				FActorSpawnParameters spawnParams;
				FRotator rotator;
				AMyMonster* myMonster;
				FPlatformProcess::Sleep(0.1f);
				myMonster = GetWorld()->SpawnActor<AMyMonster>(AMyMonster::StaticClass(), i.Value.D_SpawnPosition, rotator, spawnParams);
				
				if (myMonster == nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("MyMonster is null "));
				}

				if (myMonster)
				{
					myMonster->m_MonsterNo = i.Key;
					i.Value.D_isDead = false;

					i.Value.D_DeadTime = 0.f;
				}

				
			}
			
		}

	}
	

}
