#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("绿绒袍", ({ "cloth" }) );
        set("level",8);        
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
		set("value", 1000);
                set("armor_prop/armor", 5);

        }
        setup();
}

