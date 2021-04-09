// yuanxiang.c 软香鞋

#include <armor.h>
#include <ansi.h>

inherit BOOTS;


void create()
{
	set_name(RED "软香鞋" NOR, ({ "shoes","yuanxiang","xie","yuanxiangxie" }) );
	set("level",5);
	set_weight(900);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", "一双小巧温软的绣花鞋。  \n");
		set("material", "cloth");
		set("unit", "双");
		set("value", 2000);
		set("armor_prop/armor", 1 );
		set("armor_prop/personality", 3);
		set("female_only", 1);
	}
	setup();
}

