// magua.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("马褂", ({ "magua"}));
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
		set("value", 500);
                set("material", "cloth");
                set("armor_prop/armor", 5);
                        set("level",3);
        }
        setup();
}

