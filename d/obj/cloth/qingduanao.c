// magua.c

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("青缎袄", ({"qingduan ao", "ao"}));
                set("level",1);
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("value", 250);
                set("material", "cloth");
                set("armor_prop/armor", 2);
        }
        setup();
}

