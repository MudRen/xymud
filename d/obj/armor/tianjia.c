// golden_armor.c

#include <armor.h>

inherit ARMOR;

void create()
{
	set_name("天兵战甲", ({ "heaven armor", "armor" }) );
	set_level(10);
	set_weight(25000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("material", "gold");
		set("value", 4000);
		set("armor_prop/armor", 30);
	}
	setup();
}
