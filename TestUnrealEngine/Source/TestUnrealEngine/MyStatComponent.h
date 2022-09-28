// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTUNREALENGINE_API UMyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyStatComponent();

	void SetLevel(int32 Level);
	void SetHp(int32 NewHp);
	void OnAttacked(float DamageAmount);
	void RecoverHp(float Health);

	int32 GetLevel() { return Level; }
	int32 GetHP() { return Hp; }
	int32 GetMaxHP() { return MaxHp; }
	float GetHpRatio() { return Hp / (float)MaxHp; }
	int32 GetAttack() { return Attack; }

	FOnHpChanged OnHpChanged;

protected:

	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;


private:
	UPROPERTY(EditAnywhere, Category=Stat, Meta=(AllowPrivateAccess=true))
	int32 Level;
	
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Hp;
	
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Attack;

		
};
