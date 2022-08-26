// Fill out your copyright notice in the Description page of Project Settings.


#include "MonAnimInstance.h"
#include "MyMonster.h"

UMonAnimInstance::UMonAnimInstance()
{
	/*static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/Yin_Skeleton_Montage.Yin_Skeleton_Montage'"));

	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}*/
}
void UMonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();

	/*	auto Monster = Cast<AMyMonster>(Pawn);
		if (Monster)
		{
			IsFalling = Monster->GetMovementComponent()->IsFalling();

			Vertical = Monster->UpDownValue;
			Horizontal = Monster->LeftRightValue;
		}*/

	}
}