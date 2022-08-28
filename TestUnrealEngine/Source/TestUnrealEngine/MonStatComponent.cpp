#include "MonStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"


UMonStatComponent::UMonStatComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
	Level = 1;
}


// Called when the game starts
void UMonStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMonStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetLevel(Level);
}

void UMonStatComponent::SetLevel(int32 NewLevel)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto MonData = MyGameInstance->GetMonsterData(NewLevel);
		if (MonData)
		{
			Level = MonData->D_MonsterLevel;
			Hp=MonData->D_MonsterMaxHp;
			//SetHp(MonData->D_MonsterMaxHp);
			MaxHp = MonData->D_MonsterMaxHp;
			Attack = MonData->D_MonsterAttack;

		}
	}
}

//void UMonStatComponent::SetHp(int32 NewHp)
//{
//	Hp = NewHp;
//	if (Hp < 0)
//	{
//		//UE_LOG(LogTemp, Warning, TEXT("Before Hp %d"), Hp); //-10 ����
//		Hp = 0;
//	}
//
//	//�� �κ� ����� �ϴ� �ذ�
//	//if (Hp > MaxHp)
//	//{
//	//	Hp = MaxHp;
//	//	UE_LOG(LogTemp, Warning, TEXT("Hp %d"), Hp); //0 ����
//	//	UE_LOG(LogTemp, Warning, TEXT("MaxHp %d"), MaxHp); //0 ����
//
//	//}
//	//	
//
//	//�״� �� SetHp�� OnAttacked���� ó��
//
//	OnHpChanged.Broadcast();
//}

void UMonStatComponent::OnAttacked(float DamageAmount)
{
	Hp -= DamageAmount;
	//int32 NewHp = Hp - DamageAmount;
	//SetHp(NewHp);
	UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"),Hp);
	//UE_LOG(LogTemp, Warning, TEXT("NewHp %d"), NewHp);
}



