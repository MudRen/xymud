// caoxie.c

#include <armor.h>

inherit BOOTS;

void create()
{
	set_name("草鞋", ({ "cao xie", "xie", "shoes" }) );
	set("level",1);
	set_weight(900);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "wood");
		set("unit", "双");
		set("value", 10);
		set("armor_prop/dodge", 0 );
	}
	setup();
}
