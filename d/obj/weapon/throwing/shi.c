// dart.c
#include <weapon.h>
inherit THROWING;
void create()
{
        set_name("η³ε", ({"shi kuai", "shi", "stone"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "δΊ");
                set("base_unit", "ε");
                set("base_weight", 50);
		set("fill_sea",1);
        }
        set_amount(random(10)+1);
        init_throwing(5);
        setup();
}
