// shoupi.c

#include <armor.h>

inherit NECK;

void create()
{
        set_name("围脖", ({"neck"}));
        set("level",1);
	set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "条");
		set("armor_prop/armor", 1);
        }
        setup();
}

