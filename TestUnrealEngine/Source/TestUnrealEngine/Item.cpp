
#include "Item.h"
#include "ItemInfo.h"

UItem::UItem()
{
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
	
	
}

void UItem::Use(class AMyCharacter* Character)
{

}
