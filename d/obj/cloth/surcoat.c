#include <armor.h>

inherit SURCOAT;

void create()
{
        set_name("披风", ({ "surcoat" }) );
        set("level",1);
        set_weight(1600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
		set("value", 100);
                set("armor_prop/armor", 2);
        }
        setup();
}

