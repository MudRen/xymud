#include <armor.h>

inherit BOOTS;

void create()
{
        set_name("草鞋", ({ "cao xie", "xie", "shoes" }) );
        set("level",1);
        set_weight(900);
        if( clonep() )
                set_default_object(__FILE__);
        else {
		set("long", "一双乡下人穿的草鞋．\n");
                set("material", "wood");
                set("unit", "双");
                set("value", 10);
        }
        setup();
}

