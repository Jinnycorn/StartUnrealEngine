
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

	//ReadItemPath();
	//Potion = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("POTION"));
	//Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/PotionBottles/PotionBottle_3/SM_PotionBottle_3_Glass.SM_PotionBottle_3_Glass'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/PotionBottles/PotionBottle_2/SM_PotionBottle_2_Glass.SM_PotionBottle_2_Glass'"));
	
	/*if (SM.Succeeded())
	{
		Potion->SetStaticMesh(SM.Object);
	}

	Potion->SetupAttachment(RootComponent);*/
	//Trigger->SetupAttachment(Potion);



	//Potion->SetCollisionProfileName(TEXT("MyCollectible"));
	//Trigger->SetCollisionProfileName(TEXT("MyCollectible"));
	//Trigger->SetBoxExtent(FVector(40.f, 40.f, 40.f));

	AActor* CurrentOverlappedItem = nullptr;
}


void AMyPotion::ReadItemPath()
{
	Potion = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("POTION"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/PotionBottles/PotionBottle_2/SM_PotionBottle_2_Glass.SM_PotionBottle_2_Glass'"));

	FString ItemPathTest = ItemPath.ToString();


	const TCHAR* wavLink = *ItemPathTest;
	
	UE_LOG(LogTemp, Warning, TEXT("itemPathTest: %s"), *ItemPathTest);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(wavLink);

	UE_LOG(LogTemp, Warning, TEXT("wavLink: %s"), wavLink);


	if (SM.Succeeded())
	{
		Potion->SetStaticMesh(SM.Object);
	}

	Potion->SetupAttachment(RootComponent);
	Trigger->SetupAttachment(Potion);


	Potion->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetBoxExtent(FVector(40.f, 40.f, 40.f));
}

// Called when the game starts or when spawned
void AMyPotion::BeginPlay()
{
	Super::BeginPlay();


	UMyGameInstance* GAMEINSTANCE = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GAMEINSTANCE)
	{
		AMyGameModeBase* GM = (AMyGameModeBase*)GetWorld()->GetAuthGameMode();


		ItemPath = GAMEINSTANCE->GetItemData(2)->D_ItemPath;
		FString SItemPath = ItemPath.ToString();
		UE_LOG(LogTemp, Warning, TEXT("itemPath: %s"), *SItemPath);

		ItemKey = GAMEINSTANCE->GetItemData(2)->D_ItemKey;
		ItemDisplayName = GAMEINSTANCE->GetItemData(2)->D_ItemDisplayName;
		Thumbnail = GAMEINSTANCE->GetItemData(2)->D_Thumbnail;
		Health = GAMEINSTANCE->GetItemData(2)->D_Health;

		ItemNo = GM->GM_ItemNo++;

		UE_LOG(LogTemp, Warning, TEXT("Potion: GM_ItemNo %d"), GM->GM_ItemNo);

	}


	ReadItemPath();
	
}


void AMyPotion::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyPotion::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AMyPotion::OnCharacterEndOverlap);


}

