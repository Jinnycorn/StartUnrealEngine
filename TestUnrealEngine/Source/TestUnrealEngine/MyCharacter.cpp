 // Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "MyWeapon.h"
#include "MyPotion.h"
#include "MyStatComponent.h"
#include "Components/WidgetComponent.h"
#include "MyCharacterWidget.h"

#include "Item.h"
#include "InventoryComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMyCharacter::AMyCharacter()
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f,0.f,0.f));

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonYin/Characters/Heroes/Yin/Meshes/Yin.Yin'"));


	
	
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;

	Stat = CreateDefaultSubobject<UMyStatComponent>(TEXT("STAT"));

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));

	HpBar->SetWidgetSpace(EWidgetSpace::Screen);


	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));

	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 50.f));
	}

	//AIControllerClass = AMyAIController::StaticClass();
	//AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);
		AnimInstance->OnAttackHit.AddUObject(this, &AMyCharacter::AttackCheck);
	}
	
	HpBar->InitWidget();

	auto HpWidget = Cast<UMyCharacterWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
		HpWidget->BindHp(Stat);

	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("PickUp"), EInputEvent::IE_Pressed, this, &AMyCharacter::PickUp);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);
	
}

void AMyCharacter::Attack()
{

	if (IsAttacking)
		return;

	UE_LOG(LogTemp, Log, TEXT("Character Attack!!!!"));
	AnimInstance->PlayAttackMontage();

	AnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % 3;
	
	IsAttacking = true;
}

void AMyCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 100.f;
	float AttackRadius = 50.f;

	bool bResult= GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

	FVector Vec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + Vec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor;

	if (bResult)
	{
		DrawColor = FColor::Green;
	}
	else
	{
		DrawColor = FColor::Red;
	}


	DrawDebugCapsule(
		GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		Rotation,
		DrawColor,
		false,
		2.f
	);
	if (bResult && HitResult.Actor.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitResult.Actor->GetName());
		FDamageEvent DamageEvent;
		HitResult.Actor->TakeDamage(Stat->GetAttack(),
		DamageEvent,GetController(), this);
	}
}


void AMyCharacter::PickUp()
{
	
	if (CurrentOverlappedItem != nullptr)
	{
		auto test = CurrentOverlappedItem->GetClass()->GetFName();
		//UE_LOG(LogTemp, Log, TEXT("test is %s"), *test.ToString());
				
		if (test.ToString() == "MyWeapon")
		{

			AMyWeapon* MyWeapon = Cast<AMyWeapon>(CurrentOverlappedItem);
			UItem* Item = NewObject<UItem>(); //유아이	

			Item->ItemKey = MyWeapon->ItemKey;
			Item->Thumbnail = MyWeapon->Thumbnail;
			Item->ItemDisplayName = MyWeapon->ItemDisplayName;
			Inventory->AddItem(Item);

			UE_LOG(LogTemp, Warning, TEXT("Weapon: Destroy_ItemNo %d"), MyWeapon->ItemNo);
			
			CurrentOverlappedItem->Destroy();

			
		}
		else if (test.ToString() == "MyPotion")
		{

			AMyPotion* MyPotion = Cast<AMyPotion>(CurrentOverlappedItem);
			UItem* Item = NewObject<UItem>(); 

			Item->ItemKey = MyPotion->ItemKey;
			Item->Thumbnail = MyPotion->Thumbnail;
			Item->ItemDisplayName = MyPotion->ItemDisplayName;
			Inventory->AddItem(Item);

			UE_LOG(LogTemp, Warning, TEXT("Potion: Destroy_ItemNo %d"), MyPotion->ItemNo);

			CurrentOverlappedItem->Destroy();
		}

	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("CurrentOverlapped item is null"));
	}

}

void AMyCharacter::UpDown(float Value)
{
	
	UpDownValue = Value;
	AddMovementInput(GetActorForwardVector(), Value);

}

void AMyCharacter::LeftRight(float Value)
{
	
	LeftRightValue = Value;
	AddMovementInput(GetActorRightVector(), Value);
}


void AMyCharacter::Yaw(float Value)
{

	AddControllerYawInput(Value);
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	//OnAttackEnd.Broadcast();
}

float AMyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Stat->OnAttacked(DamageAmount);

	return DamageAmount;
}

//여기!!!!!!
float AMyCharacter::TakeHp(float Health)
{
	Stat->RecoverHp(Health);

	return Health;
}


//인벤토리로부터 아이템을 빼는 것
void AMyCharacter::EquipItemFromInventory(class UItem* Item)
{
	if (Item)
	{
		if (Item->ItemDisplayName.ToString() == "Weapon")
		{
			AMyWeapon* WeaponForEquip;
			WeaponForEquip = GetWorld()->SpawnActor<AMyWeapon>();
			//정보 채우기
			WeaponForEquip->Thumbnail = Item->Thumbnail;
			WeaponForEquip->ItemDisplayName = Item->ItemDisplayName;

			Item->Use(this);
			//Item->OnUse(this); //BP event <--안불리고 있었음
			WeaponForEquip->EquipWeapon(this);
		}

		if(Item->ItemDisplayName.ToString() == "Potion")
		{
			UE_LOG(LogTemp, Log, TEXT("I EAT POTION!!!!"));
			
			//AMyPotion* PotionForEat; 
			//PotionForEat->Thumbnail = Item->Thumbnail;
			//PotionForEat->ItemDisplayName = Item->ItemDisplayName;
			Item->Use(this);
			auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (MyGameInstance)
			{
				int32 Health = MyGameInstance->GetItemData(2)->D_Health;
				
				//여기!!
				TakeHp(Health); //여기꺼 아이템 테이블껄로 
			}
			
			
			
		}
		

	}


	


}
