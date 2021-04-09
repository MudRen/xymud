#include <armor.h>

inherit CLOTH;

void create()
{
	set_name("雪山白袍", ({"baipao", "pao", "cloth"}));
	        set("level",14);
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","一件丝制白袍，当胸绣着一只飞扬欲脱的大鹏鸟。\n");
		set("material", "cloth");
		set("unit", "件");
		set("value", 600);
		set("armor_prop/armor", 4);
		set("armor_prop/personality", 1);
	}
	setup();
}


