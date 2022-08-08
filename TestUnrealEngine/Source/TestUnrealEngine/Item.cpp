
#include "Item.h"
#include "ItemInfo.h"
#include "MyWeapon.h"
#include "InventoryComponent.h"
#include "MyCharacter.h"

UItem::UItem()
{
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
	
	
	
}

void UItem::Use(class AMyCharacter* Character)
{
	//������ Ŭ���ϸ� ������ Ŭ�������� �Ͼ ����
	//����ߴٴ� ���̴ϱ� �κ��丮���� Item�� �����ָ� �� 
	UE_LOG(LogTemp, Log, TEXT("CLICKED!!"));
	
	Character->Inventory->RemoveItem(this);

	
}
