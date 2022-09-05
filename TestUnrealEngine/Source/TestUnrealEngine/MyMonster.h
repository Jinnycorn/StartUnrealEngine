// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyMonster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class TESTUNREALENGINE_API AMyMonster : public ACharacter
{
	GENERATED_BODY()

public:

	AMyMonster();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* IDataTable;

protected:

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack();
	void AttackCheck();
	void Die();
	void SpawnRewardItem();

	FOnAttackEnd OnAttackEnd;

	void UpDown(float Value);
	void LeftRight(float Value);

	//FVector  MonsterDeadLocation;


	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


private:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Pawn)
	bool IsAttacking = false;

	UPROPERTY(VisibleAnywhere)
	bool IsDead= false;

	UPROPERTY()
	class UMonAnimInstance* MAnimInstance;

	UPROPERTY()
	int32 AttackIndex = 0;

public:
	UPROPERTY()
	float UpDownValue = 0;

	UPROPERTY()
	float LeftRightValue = 0;

	UPROPERTY(VisibleAnywhere)
	class UMonStatComponent* MonStat;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MonsterRewardItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText RewardItemType;

	

};
