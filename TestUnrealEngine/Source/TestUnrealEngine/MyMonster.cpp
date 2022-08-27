#include "MyMonster.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MonAnimInstance.h"

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


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonZinx/Characters/Heroes/Zinx/Meshes/Zinx.Zinx'"));


	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}
}

// Called when the game starts or when spawned
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
		//AnimInstance->OnAttackHit.AddUObject(this, &AMyMonster::AttackCheck);
	}

	//HpBar->InitWidget();

	//auto HpWidget = Cast<UMyCharacterWidget>(HpBar->GetUserWidgetObject());
	//if (HpWidget)
	//	HpWidget->BindHp(Stat);


}

void AMyMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyMonster::Attack);

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

void AMyMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	//OnAttackEnd.Broadcast();
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

