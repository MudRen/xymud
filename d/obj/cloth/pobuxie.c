//pobuxie.c
#include <armor.h>

inherit BOOTS;

void create()
{
	set_name("破布鞋", ({"po buxie", "buxie", "shoes"}));
	set("level",1);
	set_weight(800);
	if( clonep() ) set_default_object(__FILE__);
	else 
	{
		set("unit", "双");
		set("material", "cloth");
		set("armor_prop/armor", 1);
	}
	setup();
}

