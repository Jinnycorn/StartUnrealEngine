
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


UCLASS()
class TESTUNREALENGINE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()	

public:
	AMyCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack();
	void AttackCheck();
	void PickUp();

	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);


	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	float TakeHp(float Health);

	float& getUpDownValue() { return m_UpDownValue; }
	float& getLeftRightValue() { return m_LeftRightValue; }


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere)
	class UMyStatComponent* Stat;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

	UPROPERTY(VisibleAnywhere)
	class AActor* CurrentOverlappedItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION(BlueprintCallable, Category = "Items")
	void EquipItemFromInventory(class UItem* Item);

	
protected:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


private:
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category=Pawn)
	bool IsAttacking = false;

	UPROPERTY()
	class UMyAnimInstance* AnimInstance;

	UPROPERTY()
	int32 AttackIndex=0;


	UPROPERTY()
	float m_UpDownValue = 0;

	UPROPERTY()
	float m_LeftRightValue = 0;
};
