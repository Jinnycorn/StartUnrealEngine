
#include "ItemBase.h"
#include "MyCharacter.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AItemBase::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Log, TEXT("Overlapped"));

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor); //Cast�� �ڽ��� ĳ���ͷ� �ٲ��ذ�
	//Cast�� ���� Ÿ���� ã���ִ� ������ �ǹ�


	if (MyCharacter) //�� ĳ�����϶��� �����ϰڴ�
	{
		MyCharacter->CurrentOverlappedItem = this;

	}
}

void AItemBase::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);


	if (MyCharacter)
	{
		MyCharacter->CurrentOverlappedItem = nullptr;

	}
}