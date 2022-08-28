// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTUNREALENGINE_API UMonStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;


public:
	void SetLevel(int32 Level);
	//void SetHp(int32 NewHp);
	void OnAttacked(float DamageAmount);
	//void RecoverHp(float Health);

	int32 GetLevel() { return Level; }
	int32 GetHP() { return Hp; }
	//int32 GetMaxHP() { return MaxHp; }
	//float GetHpRatio() { return Hp / (float)MaxHp; }
	int32 GetAttack() { return Attack; }

private:
	UPROPERTY(EditAnywhere, Category = MonStat, Meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, Category = MonStat, Meta = (AllowPrivateAccess = true))
	int32 Hp;

	UPROPERTY(EditAnywhere, Category = MonStat, Meta = (AllowPrivateAccess = true))
	int32 MaxHp;

	UPROPERTY(EditAnywhere, Category = MonStat, Meta = (AllowPrivateAccess = true))
	int32 Attack;
		
};
