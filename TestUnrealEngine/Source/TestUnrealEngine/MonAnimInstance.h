// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnMonsterAttackHit);

UCLASS()
class TESTUNREALENGINE_API UMonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void MonPlayAttackMontage();

	void JumpToSection(int32 SectionIndex);

	FName GetAttackMontageName(int32 SectionIndex);

	FOnMonsterAttackHit OnMonAttackHit;
	

private:
	UFUNCTION()
	void AnimNotify_AttackHit();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* MonAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Vertical;

	
};
