// Fill out your copyright notice in the Description page of Project Settings.


#include "MonAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyMonster.h"

UMonAnimInstance::UMonAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMON(TEXT("AnimMontage'/Game/Animations/Zinx_Skeleton_Montage.Zinx_Skeleton_Montage'"));
    

	if (AMON.Succeeded())
	{
		MonAttackMontage = AMON.Object;
	}

	
}
void UMonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();
	if (IsValid(pawn))
	{
		Speed = pawn->GetVelocity().Size();

		auto monster = Cast<AMyMonster>(pawn);
		if (monster)
		{
			IsFalling = monster->GetMovementComponent()->IsFalling();

			Vertical = monster->getUpDownValue();
			Horizontal = monster->getLeftRightValue();
		}

	}
}

void UMonAnimInstance::MonPlayAttackMontage()
{
	Montage_Play(MonAttackMontage, 1.f);

}

void UMonAnimInstance::JumpToSection(int32 SectionIndex)
{

	FName name = GetAttackMontageName(SectionIndex);
	
	Montage_JumpToSection(name, MonAttackMontage);

	
}

FName UMonAnimInstance::GetAttackMontageName(int32 SectionIndex)
{

	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UMonAnimInstance::AnimNotify_AttackHit()
{
	OnMonAttackHit.Broadcast();
}