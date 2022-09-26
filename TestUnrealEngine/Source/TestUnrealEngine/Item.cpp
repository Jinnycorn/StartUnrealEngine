
#include "Item.h"
#include "MyWeapon.h"
#include "InventoryComponent.h"
#include "MyCharacter.h"

UItem::UItem()
{
	m_ItemDisplayName = FText::FromString("Item");

	
}

void UItem::Use(class AMyCharacter* Character)
{
	
	Character->Inventory->RemoveItem(this);
	
}
