#include "MyStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

UMyStatComponent::UMyStatComponent()
{

	PrimaryComponentTick.bCanEverTick =false;

	bWantsInitializeComponent = true;
	Level = 1;
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetLevel(Level);
}

void UMyStatComponent::SetLevel(int32 NewLevel)
{
	auto myGameInstance=Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (myGameInstance)
	{
		auto statData = myGameInstance->GetStatData(NewLevel);
		if (statData)
		{
			Level = statData->Level;
			SetHp(statData->MaxHp);
			MaxHp = statData->MaxHp;
			Attack = statData->Attack;

		}
	}
}

void UMyStatComponent::SetHp(int32 NewHp)
{
	Hp = NewHp;
	if (Hp < 0)
	{
		Hp = 0;
	}


	OnHpChanged.Broadcast();
}

void UMyStatComponent::OnAttacked(float DamageAmount)
{
	
	int32 newHp = Hp - DamageAmount;
	SetHp(newHp);

}

void UMyStatComponent::RecoverHp(float Health)
{

	int32 newHp = Hp + Health;
	SetHp(newHp);

}
