// shoupi.c

#include <armor.h>

inherit WAIST;

void create()
{
        set_name("腰带", ({"waist"}));
        set("level",1);
	set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "leather");
                set("unit", "条");
		set("armor_prop/armor", 1);
        }
        setup();
}

