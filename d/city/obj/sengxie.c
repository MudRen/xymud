#include <armor.h>

inherit BOOTS;

void create()
{
	set_name( "僧鞋", ({ "seng xie", "xie" }) );
	set("level",2);
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "双");
		set("long", "一双圆口青布僧鞋。");
		set("value", 6000);
		set("material", "boots");
		set("armor_prop/dodge", 5);
	}
	setup();
}
