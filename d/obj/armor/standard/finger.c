// shoupi.c

#include <armor.h>

inherit FINGER;

void create()
{
        set_name("指套", ({"finger"}));
        set("level",1);
	set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "iron");
                set("unit", "套");
		set("armor_prop/armor", 1);
        }
        setup();
}

