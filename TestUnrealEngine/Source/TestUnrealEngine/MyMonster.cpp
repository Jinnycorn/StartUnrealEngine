#include "MyMonster.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MonAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "MonStatComponent.h"
#include "Components/WidgetComponent.h"
#include "MyCharacterWidget.h"
#include "MyAIController.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "ItemBase.h"
#include "MyWeapon.h"
#include "MyPotion.h"

AMyMonster::AMyMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	GetMesh()->SetRelativeLocationAndRotation(
	FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	//1. 캐릭터 매쉬
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonZinx/Characters/Heroes/Zinx/Meshes/Zinx.Zinx'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonCountess/Characters/Heroes/Countess/Meshes/SM_Countess.SM_Countess'"));


	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	MonStat = CreateDefaultSubobject<UMonStatComponent>(TEXT("MONSTAT"));

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));

	HpBar->SetWidgetSpace(EWidgetSpace::Screen);

	//원래 이부분 없었음
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> BP_MonAnim(TEXT
	("AnimBlueprint'/Game/Blueprints/ABP_CMonAnim.ABP_CMonAnim_C'"));
	if (BP_MonAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BP_MonAnim.Class);
		UE_LOG(LogTemp, Warning, TEXT("MonAnim Succeeded"));
	}

	


	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));

	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 50.f));
	}

	AIControllerClass = AMyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AMyMonster::BeginPlay()
{
	Super::BeginPlay();
	
	//임시로
	//SpawnRewardItem();
}

void AMyMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MAnimInstance = Cast<UMonAnimInstance>(GetMesh()->GetAnimInstance());
	
	
	if (MAnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("MonAnimInstance also Succeeded"));
		MAnimInstance->OnMontageEnded.AddDynamic(this, &AMyMonster::OnAttackMontageEnded);
		MAnimInstance->OnMonAttackHit.AddUObject(this, &AMyMonster::AttackCheck);
	}

	
	HpBar->InitWidget();

	auto HpWidget = Cast<UMyCharacterWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
		HpWidget->BindMonHp(MonStat);


}

void AMyMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyMonster::Attack);

}

void AMyMonster::Attack()
{

	if (IsAttacking)
		return;


	MAnimInstance->MonPlayAttackMontage();

	MAnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % 3;

	IsAttacking = true;

}

void AMyMonster::AttackCheck()
{
	FHitResult HitResult;

	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 100.f;
	float AttackRadius = 50.f;

	bool bResult = GetWorld()->SweepSingleByChannel(
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
		UE_LOG(LogTemp, Log, TEXT("Monster's Hit Actor: %s"), *HitResult.Actor->GetName());
		FDamageEvent DamageEvent;
		HitResult.Actor->TakeDamage(MonStat->GetAttack(),
			DamageEvent, GetController(), this);
	}
}

void AMyMonster::Die()
{
	
	//hp가 0이 되면 이 함수 불릴 것
	UE_LOG(LogTemp, Log, TEXT("Monster Dead"));
	IsDead = true;

	if (IsDead == true)
	{
		SpawnRewardItem();
		this->Destroy();
	}
}

void AMyMonster::SpawnRewardItem()
{
	UMyGameInstance* GAMEINSTANCE = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));


	if (GAMEINSTANCE)
	{

		//FText SomeText = FText::FromString("Something");
		//FString SomeString = SomeText.ToString();
		//UE_LOG(LogTemp, Log, TEXT("SomeString: %s"), *SomeString); 


		MonsterRewardItemKey = GAMEINSTANCE->GetItemData(2)->D_ItemKey;
		RewardItemType= GAMEINSTANCE->GetItemData(MonsterRewardItemKey)->D_ItemType;
		FString RT = RewardItemType.ToString();

		if (RT == "Weapon")
		{

			UE_LOG(LogTemp, Warning, TEXT("RT should be Weapon: %s"), *RT);
		}
		else if (RT == "Potion")
		{
			//얘도 되고(죽은자리에 생김)
			UWorld* world = GetWorld();
			if (world)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				FRotator rotator;
				FVector  SpawnLocation = GetActorLocation();
				SpawnLocation.Z -= 90.0f;

				world->SpawnActor<AMyPotion>(SpawnLocation, rotator, SpawnParams);
			}

			//얘도 되고
		/*	UE_LOG(LogTemp, Warning, TEXT("RT should be Potion: %s"), *RT);
			FTransform SpawnLocation;
			GetWorld()->SpawnActor<AMyPotion>(AMyPotion::StaticClass(), SpawnLocation);*/
		}
		
		//UE_LOG(LogTemp, Warning, TEXT("MonsterRewardItemKey: %d"), MonsterRewardItemKey);
		
	}


}

void AMyMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

void AMyMonster::UpDown(float Value)
{

	UpDownValue = Value;
	AddMovementInput(GetActorForwardVector(), Value);

}

void AMyMonster::LeftRight(float Value)
{

	LeftRightValue = Value;
	AddMovementInput(GetActorRightVector(), Value);
}

float AMyMonster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	MonStat->OnAttacked(DamageAmount);

	if (MonStat->OnAttacked(DamageAmount))
	{
		Die();
	}
	return DamageAmount;
}



