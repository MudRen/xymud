#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("阿拉伯长袍", ({ "chang pao", "pao", "cloth" }) );
        set("level",2);
	set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "件");
                set("value", 80);
		set("armor_prop/armor", 2);

        }
        setup();
}

