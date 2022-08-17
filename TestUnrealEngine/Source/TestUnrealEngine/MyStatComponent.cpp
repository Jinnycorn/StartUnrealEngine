// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick =false;

	bWantsInitializeComponent = true;
	Level = 1;
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetLevel(Level);
}

void UMyStatComponent::SetLevel(int32 NewLevel)
{
	auto MyGameInstance=Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto StatData = MyGameInstance->GetStatData(NewLevel);
		if (StatData)
		{
			Level = StatData->Level;
			SetHp(StatData->MaxHp);
			MaxHp = StatData->MaxHp;
			Attack = StatData->Attack;

		}
	}
}

void UMyStatComponent::SetHp(int32 NewHp)
{
	Hp = NewHp;
	if (Hp < 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Before Hp %d"), Hp); //-10 나옴
		Hp = 0;
	}
		
	//이 부분 지우면 일단 해결
	//if (Hp > MaxHp)
	//{
	//	Hp = MaxHp;
	//	UE_LOG(LogTemp, Warning, TEXT("Hp %d"), Hp); //0 나옴
	//	UE_LOG(LogTemp, Warning, TEXT("MaxHp %d"), MaxHp); //0 나옴

	//}
	//	
	
	//죽는 거 SetHp나 OnAttacked에서 처리

	OnHpChanged.Broadcast();
}

void UMyStatComponent::OnAttacked(float DamageAmount)
{
	
	int32 NewHp = Hp - DamageAmount;
	SetHp(NewHp);
	//UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"),Hp);
	//UE_LOG(LogTemp, Warning, TEXT("NewHp %d"), NewHp);
}

void UMyStatComponent::RecoverHp(float Health)
{

	int32 NewHp = Hp + Health;
	SetHp(NewHp);
	//UE_LOG(LogTemp, Warning, TEXT("RecoverHp %d"),Hp);
	//UE_LOG(LogTemp, Warning, TEXT("NewHp %d"), NewHp);
}
