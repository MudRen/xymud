#include <armor.h>

inherit WRISTS;

void create()
{
        set_name("护腕", ({ "wrists" }) );
        set("level",1);
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("material", "copper");
		set("value", 100);
                set("armor_prop/armor", 2);
        }
        setup();
}

