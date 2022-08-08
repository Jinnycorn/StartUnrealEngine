
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
	//아이템 클릭하면 아이템 클래스에서 일어날 일은
	//사용했다는 것이니까 인벤토리에서 Item을 지워주면 됨 
	UE_LOG(LogTemp, Log, TEXT("CLICKED!!"));
	
	Character->Inventory->RemoveItem(this);

	
}
