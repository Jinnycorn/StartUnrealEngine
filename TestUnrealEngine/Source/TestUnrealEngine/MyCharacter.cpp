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


AMyCharacter::AMyCharacter()
{

 	
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

}


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

	auto hpWidget = Cast<UMyCharacterWidget>(HpBar->GetUserWidgetObject());
	if (hpWidget)
		hpWidget->BindHp(Stat);

	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


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

	AnimInstance->PlayAttackMontage();
	AnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % 3;
	
	IsAttacking = true;
}

void AMyCharacter::AttackCheck()
{
	
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 100.f;
	float attackRadius = 50.f;

	bool bResult= GetWorld()->SweepSingleByChannel(
		OUT hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(attackRadius),
		params
	);


	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;
	float halfHeight = attackRange * 0.5f + attackRadius;
	FQuat rotation = FRotationMatrix::MakeFromZ(vec).ToQuat();
	FColor drawColor;

	if (bResult)
	{
		
		drawColor = FColor::Green;
	}
	else
	{
		
		drawColor = FColor::Red;
	}


	DrawDebugCapsule(
		GetWorld(),
		center,
		halfHeight,
		attackRadius,
		rotation,
		drawColor,
		false,
		2.f
	);
	if (bResult && hitResult.Actor.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *hitResult.Actor->GetName());
		FDamageEvent damageEvent;
		hitResult.Actor->TakeDamage(Stat->GetAttack(),
		damageEvent,GetController(), this);
	}
}


void AMyCharacter::PickUp()
{
	
	if (CurrentOverlappedItem != nullptr)
	{
		auto overlappedItem = CurrentOverlappedItem->GetClass()->GetFName();
				
		if (overlappedItem.ToString() == "MyWeapon")
		{

			AMyWeapon* myWeapon = Cast<AMyWeapon>(CurrentOverlappedItem);
			UItem* item = NewObject<UItem>(); 

			item->m_ItemKey = myWeapon->m_ItemKey;
			item->m_Thumbnail = myWeapon->m_Thumbnail;
			item->m_ItemDisplayName = myWeapon->m_ItemDisplayName;
			Inventory->AddItem(item);

			UE_LOG(LogTemp, Warning, TEXT("Weapon: Destroy_ItemNo %d"), myWeapon->m_ItemNo);
			
			CurrentOverlappedItem->Destroy();

			
		}
		else if (overlappedItem.ToString() == "MyPotion")
		{

			AMyPotion* myPotion = Cast<AMyPotion>(CurrentOverlappedItem);
			UItem* item = NewObject<UItem>(); 

			item->m_ItemKey = myPotion->m_ItemKey;
			item->m_Thumbnail = myPotion->m_Thumbnail;
			item->m_ItemDisplayName = myPotion->m_ItemDisplayName;
			Inventory->AddItem(item);

			UE_LOG(LogTemp, Warning, TEXT("Potion: Destroy_ItemNo %d"), myPotion->m_ItemNo);

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

}

float AMyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Stat->OnAttacked(DamageAmount);

	return DamageAmount;
}


float AMyCharacter::TakeHp(float Health)
{
	Stat->RecoverHp(Health);

	return Health;
}


void AMyCharacter::EquipItemFromInventory(class UItem* Item)
{
	if (Item)
	{
		if (Item->m_ItemDisplayName.ToString() == "Weapon")
		{
			AMyWeapon* weaponForEquip;
			weaponForEquip = GetWorld()->SpawnActor<AMyWeapon>();
			weaponForEquip->m_Thumbnail = Item->m_Thumbnail;
			weaponForEquip->m_ItemDisplayName = Item->m_ItemDisplayName;

			Item->Use(this);
			weaponForEquip->EquipWeapon(this);
		}

		if(Item->m_ItemDisplayName.ToString() == "Potion")
		{
			UE_LOG(LogTemp, Log, TEXT("I EAT POTION!!!!"));
			
			
			Item->Use(this);
			auto myGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (myGameInstance)
			{
				int32 health = myGameInstance->GetItemData(2)->D_Health;
				TakeHp(health); 
			}
	
			
		}

	}

}
