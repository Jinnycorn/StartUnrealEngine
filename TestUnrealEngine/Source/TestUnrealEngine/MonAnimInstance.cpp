// Fill out your copyright notice in the Description page of Project Settings.


#include "MonAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyMonster.h"

UMonAnimInstance::UMonAnimInstance()
{
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> AMON(TEXT("AnimMontage'/Game/Animations/Zinx_Skeleton_Montage.Zinx_Skeleton_Montage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMON(TEXT("AnimMontage'/Game/Animations/S_Countess_Skeleton_Montage.S_Countess_Skeleton_Montage'"));

	if (AMON.Succeeded())
	{
		MonAttackMontage = AMON.Object;
	}
}
void UMonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();

		auto Monster = Cast<AMyMonster>(Pawn);
		if (Monster)
		{
			IsFalling = Monster->GetMovementComponent()->IsFalling();

			Vertical = Monster->UpDownValue;
			Horizontal = Monster->LeftRightValue;
		}

	}
}

void UMonAnimInstance::MonPlayAttackMontage()
{
	Montage_Play(MonAttackMontage, 1.f);

}

void UMonAnimInstance::JumpToSection(int32 SectionIndex)
{

	FName Name = GetAttackMontageName(SectionIndex);
	
	Montage_JumpToSection(Name, MonAttackMontage);

	
}

FName UMonAnimInstance::GetAttackMontageName(int32 SectionIndex)
{

	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UMonAnimInstance::AnimNotify_AttackHit()
{
	//UE_LOG(LogTemp, Log, TEXT("MonsterAnimNotify_AttackHit"));
	OnMonAttackHit.Broadcast();
}