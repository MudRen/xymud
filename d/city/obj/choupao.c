// linen.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("绸袍", ({"choupao"}));
        set("level",2);
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 1000);
                set("armor_prop/armor", 5);
                        set("level",2);
        }
        setup();
}

