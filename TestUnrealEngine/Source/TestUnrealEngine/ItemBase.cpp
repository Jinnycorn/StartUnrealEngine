
#include "ItemBase.h"
#include "MyCharacter.h"


AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	itemlist[0] = FString(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_HeroSword22/SK_Blade_HeroSword22.SK_Blade_HeroSword22'"));
	itemlist[1]= FString(TEXT("StaticMesh'/Game/PotionBottles/PotionBottle_2/SM_PotionBottle_2_Glass.SM_PotionBottle_2_Glass'"));
	itemlist[2]= FString(TEXT("StaticMesh'/Game/PotionBottles/PotionBottle_3/SM_PotionBottle_3_Glass.SM_PotionBottle_3_Glass'"));

}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}


void AItemBase::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AMyCharacter* myCharacter = Cast<AMyCharacter>(OtherActor); 

	if (myCharacter)
	{
		myCharacter->CurrentOverlappedItem = this;

	}
}

void AItemBase::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* myCharacter = Cast<AMyCharacter>(OtherActor);


	if (myCharacter)
	{
		myCharacter->CurrentOverlappedItem = nullptr;

	}
}
