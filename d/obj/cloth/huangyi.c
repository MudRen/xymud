// linen.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("黄色小褂", ({"yellow cloth", "cloth"}));
        set("level",1);
	set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 100);
		set("armor_prop/armor", 5);

        }
        setup();
}

