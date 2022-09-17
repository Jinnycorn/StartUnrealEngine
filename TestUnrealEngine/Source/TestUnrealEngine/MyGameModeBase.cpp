// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"


AMyGameModeBase::AMyGameModeBase()
{

	PrimaryActorTick.bCanEverTick = true;
	//�ڵ�� �� ��
	//DefaultPawnClass = AMyCharacter::StaticClass();
	
	//��� ����Ʈ�� �ٲٱ�
	static ConstructorHelpers::FClassFinder<ACharacter>BP_Char(TEXT("Blueprint'/Game/Blueprints/BP_MyCharacter.BP_MyCharacter_C'"));

	if (BP_Char.Succeeded())
	{
		DefaultPawnClass = BP_Char.Class;
	}

	
	GM_ItemNo = 0;

	//���� ���� ���̺��� ������ ���� �ʿ� �־��ֱ�
	
	//MonsterSpawnTable �ʱ�ȭ
	static ConstructorHelpers::FObjectFinder<UDataTable> SPAWNDATA(TEXT("DataTable'/Game/Data/MonsterSpawnTable.MonsterSpawnTable'"));
	if (SPAWNDATA.Succeeded())
	{
		//UE_LOG(LogTemp, Warning, TEXT("SpawnDataTable Succeed!"));
		SpawnDataTable = SPAWNDATA.Object;
	}

	//���������̺��� monsterNo
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
	//UE_LOG(LogTemp, Warning, TEXT("DT is  %f"),GameTime); //�� ���� 1,2�ʾ�


}

