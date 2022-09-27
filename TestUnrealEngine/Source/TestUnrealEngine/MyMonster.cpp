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
#include "MyGameModeBase.h"

AMyMonster::AMyMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	GetMesh()->SetRelativeLocationAndRotation(
	FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonZinx/Characters/Heroes/Zinx/Meshes/Zinx.Zinx'"));
	

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	MonStat = CreateDefaultSubobject<UMonStatComponent>(TEXT("MONSTAT"));

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));

	HpBar->SetWidgetSpace(EWidgetSpace::Screen);

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> BP_MonAnim(TEXT
	("AnimBlueprint'/Game/Blueprints/ABP_MonAnim.ABP_MonAnim_C'"));
	if (BP_MonAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BP_MonAnim.Class);

	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("MyMonster"));

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));

	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 50.f));
	}

	AIControllerClass = AMyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}


void AMyMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MAnimInstance = Cast<UMonAnimInstance>(GetMesh()->GetAnimInstance());
	
	
	if (MAnimInstance)
	{
		
		MAnimInstance->OnMontageEnded.AddDynamic(this, &AMyMonster::OnAttackMontageEnded);
		MAnimInstance->OnMonAttackHit.AddUObject(this, &AMyMonster::AttackCheck);
	}

	
	HpBar->InitWidget();

	auto hpWidget = Cast<UMyCharacterWidget>(HpBar->GetUserWidgetObject());
	if (hpWidget)
		hpWidget->BindMonHp(MonStat);


}

void AMyMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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
	FHitResult hitResult;
	
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 100.f;
	float attackRadius = 50.f;

	bool bResult = GetWorld()->SweepSingleByChannel(
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
		if (hitResult.Actor->GetClass()->GetName()==this->GetClass()->GetName())
		{
			return;
		}
		
		FDamageEvent damageEvent;
		hitResult.Actor->TakeDamage(MonStat->GetAttack(),
		damageEvent, GetController(), this);
	}
}

void AMyMonster::Die()
{
	AMyGameModeBase* GM = (AMyGameModeBase*)GetWorld()->GetAuthGameMode();
	IsDead = true;
	
	UE_LOG(LogTemp, Warning, TEXT("DeadMons's MonsterNo: %d "), m_MonsterNo);
	
	TMap<int32, FMonsterSpawnData>& monsterMap = GM->getMonsterMap();

	monsterMap.Find(m_MonsterNo)->D_isDead = true;
	
	monsterMap.Find(m_MonsterNo)->D_DeadTime = GM->m_GameTime;

	if (IsDead == true)
	{
		SpawnRewardItem();
		this->Destroy();
	}
}

void AMyMonster::SpawnRewardItem()
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));


	if (GI)
	{
		m_MonsterRewardItemKey = GI->GetItemData(2)->D_ItemKey;
		m_RewardItemType= GI->GetItemData(m_MonsterRewardItemKey)->D_ItemType;
		FString rewardtype = m_RewardItemType.ToString();

		if (rewardtype == "Weapon")
		{

			UE_LOG(LogTemp, Warning, TEXT("RT should be Weapon: %s"), *rewardtype);
		}
		else if (rewardtype == "Potion")
		{
			UWorld* world = GetWorld();
			if (world)
			{
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = this;
				FRotator rotator;
				FVector  spawnLocation = GetActorLocation();
				spawnLocation.Z -= 90.0f;

				world->SpawnActor<AMyPotion>(spawnLocation, rotator, spawnParams);
			}

		}
		
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



