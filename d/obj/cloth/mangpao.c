#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("大红蟒袍", ({"mangpao", "cloth"}));
                set("level",12);
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
		set("long",
"一件大红色的长袍，上绣一条青龙，还有日月山河的图形．\n");
                set("material", "cloth");
                set("unit", "件");
                set("value", 7000);
                set("armor_prop/armor", 15);

        }
        setup();
}

