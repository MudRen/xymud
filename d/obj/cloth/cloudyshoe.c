#include <armor.h>
inherit BOOTS;

void create()
{
        set_name("踏云靴", ({ "cloudy shoes", "shoes" }) );
        set("level",9);
        set_weight(1700);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "双");
                set("value", 4500);
                set("material", "cloth");
                set("armor_prop/armor", 2);
                set("armor_prop/dodge", 10);
        }
        setup();
}

