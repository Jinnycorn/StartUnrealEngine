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

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack();
	void AttackCheck();
	void Die();
	void SpawnRewardItem();
	void UpDown(float Value);
	void LeftRight(float Value);

	float& getUpDownValue() { return m_UpDownValue; }
	float& getLeftRightValue() { return m_LeftRightValue; }

	FOnAttackEnd OnAttackEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* IDataTable;

	UPROPERTY(VisibleAnywhere)
	class UMonStatComponent* MonStat;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_MonsterRewardItemKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText m_RewardItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_MonsterNo;


protected:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);


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

	UPROPERTY()
	float m_UpDownValue = 0;

	UPROPERTY()
	float m_LeftRightValue = 0;
};
