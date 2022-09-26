#include "MyWeapon.h"
#include "Components/BoxComponent.h"
#include "MyCharacter.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameModeBase.h"


AMyWeapon::AMyWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SW(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_HeroSword22/SK_Blade_HeroSword22.SK_Blade_HeroSword22'"));

	if (SW.Succeeded())
	{
		Weapon->SetSkeletalMesh(SW.Object);
	}

	Weapon->SetupAttachment(RootComponent);
	Trigger->SetupAttachment(Weapon);

	Weapon->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetBoxExtent(FVector(40.f, 40.f, 40.f));

	AActor* CurrentOverlappedItem = nullptr;
	
}


void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		AMyGameModeBase* GM = (AMyGameModeBase*)GetWorld()->GetAuthGameMode();
		
		m_ItemKey = GI->GetItemData(1)->D_ItemKey;
		m_ItemDisplayName = GI->GetItemData(1)->D_ItemDisplayName;
		m_Thumbnail = GI->GetItemData(1)->D_Thumbnail;

		m_ItemNo = GM->m_GM_ItemNo++;

		
	}
	
}


void AMyWeapon::EquipWeapon(AActor* OtherActor) 
{
	AMyCharacter* myCharacter = Cast<AMyCharacter>(OtherActor);
	if (myCharacter)
	{
		FName weaponSocket(TEXT("hand_l_socket"));
		AttachToComponent(myCharacter->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			weaponSocket);
	
	}
}



void AMyWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyWeapon::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AMyWeapon::OnCharacterEndOverlap);


}





