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
	
	UMyGameInstance* GAMEINSTANCE = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GAMEINSTANCE)
	{
		AMyGameModeBase* GM = (AMyGameModeBase*)GetWorld()->GetAuthGameMode();
		
		m_ItemKey = GAMEINSTANCE->GetItemData(1)->D_ItemKey;
		m_ItemDisplayName = GAMEINSTANCE->GetItemData(1)->D_ItemDisplayName;
		m_Thumbnail = GAMEINSTANCE->GetItemData(1)->D_Thumbnail;

		m_ItemNo = GM->m_GM_ItemNo++;
		UE_LOG(LogTemp, Warning, TEXT("Weapon: GM_ItemNo %d"), GM->m_GM_ItemNo);
		
	}
	
}


void AMyWeapon::EquipWeapon(AActor* OtherActor) 
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		FName WeaponSocket(TEXT("hand_l_socket"));
		AttachToComponent(MyCharacter->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			WeaponSocket);
	
	}
}



void AMyWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyWeapon::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AMyWeapon::OnCharacterEndOverlap);


}





