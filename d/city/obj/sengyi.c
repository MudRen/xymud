// linen.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("僧衣", ({"seng yi", "cloth"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("armor_prop/armor", 2);
		set("level",1);
        }
        setup();
}

