// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "Components/BoxComponent.h"
#include "MyCharacter.h"
#include "ItemInfo.h"
#include "MyItemDataTable.h"


AMyWeapon::AMyWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	//DataTable 초기화
	static ConstructorHelpers::FObjectFinder<UDataTable> IDT(TEXT("DataTable'/Game/Items/BP_MyItemDataTable.BP_MyItemDataTable'"));
	if (IDT.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		IDataTable = IDT.Object;
	}

	//원래 있던 자리
	/*UItemInfo* Info = NewObject<UItemInfo>();
	
	ItemDisplayName = Info->ItemDisplayName;
	Thumbnail = Info->Thumbnail;*/
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SW(TEXT("SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_HeroSword22/SK_Blade_HeroSword22.SK_Blade_HeroSword22'"));	
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SW(TEXT("StaticMesh'/Game/ParagonGreystone/FX/Meshes/Heroes/Greystone/SM_Greystone_Blade_01.SM_Greystone_Blade_01'"));
	if (SW.Succeeded())
	{
		Weapon->SetSkeletalMesh(SW.Object);
		//Weapon->SetStaticMesh(SW.Object);
	}

	Weapon->SetupAttachment(RootComponent);
	Trigger->SetupAttachment(Weapon);

	Weapon->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));

	AActor* CurrentOverlappedItem = nullptr;
	
}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();

	auto List = IDataTable->GetRowNames();
	RandomName = List[FMath::RandRange(0, 1)];
	FMyItemDataTable* ItemData = IDataTable->FindRow<FMyItemDataTable>(RandomName, FString(""));
	
	
	UItemInfo* Info = NewObject<UItemInfo>();
	ItemKey = ItemData->D_ItemKey;
	ItemDisplayName = ItemData->D_ItemDisplayName;
	Thumbnail = ItemData->D_Thumbnail;
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

//겹치기 시작했을 때 딱 한번만 불림
void AMyWeapon::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ 
	//UE_LOG(LogTemp, Log, TEXT("Overlapped"));

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor); //Cast로 자식의 캐릭터로 바꿔준것
	//Cast는 실제 타입을 찾아주는 검증의 의미
	

	if (MyCharacter) //내 캐릭터일때만 실행하겠다
	{
		MyCharacter->CurrentOverlappedItem = this;
		
		
		//이거 풀면 원래대로 동작
		/*FName WeaponSocket(TEXT("hand_l_socket"));

		AttachToComponent(MyCharacter->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			WeaponSocket);*/
	}
}

void AMyWeapon::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor); 


	if (MyCharacter) 
	{
		MyCharacter->CurrentOverlappedItem = nullptr;

	}
}



