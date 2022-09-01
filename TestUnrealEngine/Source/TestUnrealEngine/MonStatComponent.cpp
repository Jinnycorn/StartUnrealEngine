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
			SetHp(MonData->D_MonsterMaxHp);
			MaxHp = MonData->D_MonsterMaxHp;
			Attack = MonData->D_MonsterAttack;

		}
	}
}

void UMonStatComponent::SetHp(int32 NewHp)
{
	

	Hp = NewHp;
	if (Hp < 0)
	{
		Hp = 0;
		
	}


	OnMonHpChanged.Broadcast();
}

bool UMonStatComponent::OnAttacked(float DamageAmount)
{
	int32 NewHp = Hp - DamageAmount;	
	SetHp(NewHp);
	
	if (NewHp <= 0)
	{
		return true;
	}
	return false;
}



