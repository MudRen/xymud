// boots.c

#include <armor.h>
#include <ansi.h>

inherit BOOTS;

void create()
{
	set_name(YEL "雪虹布靴" NOR, ({ "shoes" }) );
	set_weight(900);
	if( clonep() )
		set_default_object(__FILE__);
	else {
                set("long", "一双小巧精致的布靴，柔软舒适。  \n");
		set("material", "cloth");
		set("unit", "双");
		set("armor_prop/armor", 10 );
		set("mod", "0002");
	}
	setup();
}
