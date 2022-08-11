
#include "MyPotion.h"
#include "Components/BoxComponent.h"
#include "MyCharacter.h"
#include "ItemInfo.h"

// Sets default values
AMyPotion::AMyPotion()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Potion = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("POTION"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SW(TEXT("StaticMesh'/Game/PotionBottles/PotionBottle_3/SM_PotionBottle_3_Glass.SM_PotionBottle_3_Glass'"));
	
	if (SW.Succeeded())
	{

		Potion->SetStaticMesh(SW.Object);
	}

	Potion->SetupAttachment(RootComponent);
	Trigger->SetupAttachment(Potion);



	Potion->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));

	AActor* CurrentOverlappedItem = nullptr;
}

// Called when the game starts or when spawned
void AMyPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPotion::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyPotion::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AMyPotion::OnCharacterEndOverlap);


}

//��ġ�� �������� �� �� �ѹ��� �Ҹ�
void AMyPotion::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Log, TEXT("Overlapped"));

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor); //Cast�� �ڽ��� ĳ���ͷ� �ٲ��ذ�


	if (MyCharacter) //�� ĳ�����϶��� �����ϰڴ�
	{
		MyCharacter->CurrentOverlappedItem = this;
		UE_LOG(LogTemp, Log, TEXT("Potion Overlapped"));
	}
}

void AMyPotion::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);


	if (MyCharacter)
	{
		MyCharacter->CurrentOverlappedItem = nullptr;

	}
}
