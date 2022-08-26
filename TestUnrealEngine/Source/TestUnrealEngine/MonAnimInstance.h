// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTUNREALENGINE_API UMonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMonAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;
};
