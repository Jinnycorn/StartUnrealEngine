// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"
#include "MyItemDataTable.h"

AMyGameModeBase::AMyGameModeBase()
{
	//코드로 할 때
	//DefaultPawnClass = AMyCharacter::StaticClass();
	
	//블루 프린트로 바꾸기
	static ConstructorHelpers::FClassFinder<ACharacter>BP_Char(TEXT("Blueprint'/Game/Blueprints/BP_MyCharacter.BP_MyCharacter_C'"));

	if (BP_Char.Succeeded())
	{
		DefaultPawnClass = BP_Char.Class;
	}

	
	GM_ItemNo = 0;

	
}


