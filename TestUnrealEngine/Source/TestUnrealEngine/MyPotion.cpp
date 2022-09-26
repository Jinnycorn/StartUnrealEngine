
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


	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(*itemlist[1]);


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


void AMyPotion::BeginPlay()
{
	Super::BeginPlay();


}

void AMyPotion::ReadItemPath()
{

	UMyGameInstance* GAMEINSTANCE = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GAMEINSTANCE)
	{
		AMyGameModeBase* GM = (AMyGameModeBase*)GetWorld()->GetAuthGameMode();

		
		ItemPath = GAMEINSTANCE->GetItemData(2)->D_ItemPath;
		m_ItemKey = GAMEINSTANCE->GetItemData(2)->D_ItemKey;
		m_ItemDisplayName = GAMEINSTANCE->GetItemData(2)->D_ItemDisplayName;
		m_Thumbnail = GAMEINSTANCE->GetItemData(2)->D_Thumbnail;
		Health = GAMEINSTANCE->GetItemData(2)->D_Health;

		m_ItemNo = GM->m_GM_ItemNo++;

	}

	
	

}

void AMyPotion::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyPotion::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AMyPotion::OnCharacterEndOverlap);


}


