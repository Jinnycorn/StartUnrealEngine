// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterWidget.h"
#include "MyStatComponent.h"
#include "MonStatComponent.h"
#include "Components/ProgressBar.h"

void UMyCharacterWidget::BindHp(class UMyStatComponent* StatComp)
{
	CurrentStatComp = StatComp;
	StatComp->OnHpChanged.AddUObject(this, &UMyCharacterWidget::UpdateHp);
	
}

void UMyCharacterWidget::BindMonHp(class UMonStatComponent* StatComp)
{
	CurrentMonStatComp = StatComp;
	StatComp->OnMonHpChanged.AddUObject(this, &UMyCharacterWidget::UpdateHp);

}

void UMyCharacterWidget::UpdateHp()
{
	if (CurrentStatComp.IsValid())
	{
		PB_HpBar->SetPercent(CurrentStatComp->GetHpRatio());
	}
	
	if (CurrentMonStatComp.IsValid())
	{
		PB_HpBar->SetPercent(CurrentMonStatComp->GetHpRatio());
	}
	
}
