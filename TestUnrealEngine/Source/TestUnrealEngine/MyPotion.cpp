
#include "MyPotion.h"
#include "Components/BoxComponent.h"
#include "MyCharacter.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameModeBase.h"


// Sets default values
AMyPotion::AMyPotion()
{
	
	PrimaryActorTick.bCanEverTick = false;

	Potion = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("POTION"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	ReadItemPath();

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/PotionBottles/PotionBottle_3/SM_PotionBottle_3_Glass.SM_PotionBottle_3_Glass'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/PotionBottles/PotionBottle_2/SM_PotionBottle_2_Glass.SM_PotionBottle_2_Glass'"));
	
	//FString test = FString(TEXT("StaticMesh'/Game/PotionBottles/PotionBottle_2/SM_PotionBottle_2_Glass.SM_PotionBottle_2_Glass'"));
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(*test[1]);


	//UE_LOG(LogTemp, Warning, TEXT("ItemPath is %s"), *ItemPath); //몬스터 죽고 아이템 생길때만 읽힘
	//UE_LOG(LogTemp, Warning, TEXT("test is %s"), *test);

	if (SM.Succeeded())
	{
		Potion->SetStaticMesh(SM.Object);
	}

	Potion->SetupAttachment(RootComponent);
	Trigger->SetupAttachment(Potion);


	Potion->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetBoxExtent(FVector(40.f, 40.f, 40.f));

	AActor* CurrentOverlappedItem = nullptr;
}

// Called when the game starts or when spawned
void AMyPotion::BeginPlay()
{
	Super::BeginPlay();
	
	//ReadItemPath();

}

void AMyPotion::ReadItemPath()
{

	//이부분은 원래 BeginPlay에 있었음
	UMyGameInstance* GAMEINSTANCE = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GAMEINSTANCE)
	{
		AMyGameModeBase* GM = (AMyGameModeBase*)GetWorld()->GetAuthGameMode();

		
		ItemPath = GAMEINSTANCE->GetItemData(2)->D_ItemPath;
		ItemKey = GAMEINSTANCE->GetItemData(2)->D_ItemKey;
		ItemDisplayName = GAMEINSTANCE->GetItemData(2)->D_ItemDisplayName;
		Thumbnail = GAMEINSTANCE->GetItemData(2)->D_Thumbnail;
		Health = GAMEINSTANCE->GetItemData(2)->D_Health;

		//FString SomeString = ItemPath.ToString();

	

		ItemNo = GM->GM_ItemNo++;
		//UE_LOG(LogTemp, Warning, TEXT("Potion: GM_ItemNo %d"), GM->GM_ItemNo);

	}

	
	

}

void AMyPotion::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyPotion::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AMyPotion::OnCharacterEndOverlap);


}


