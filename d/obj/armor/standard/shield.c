// shoupi.c

#include <armor.h>

inherit SHIELD;

void create()
{
        set_name("盾牌", ({"shield"}));
        set_level(1);
	set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "wood");
                set("unit", "面");
		set("armor_prop/armor", 5);
        }
        setup();
}

