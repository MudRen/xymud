// lightarmor.c
#include <armor.h>

inherit ARMOR;

void create()
{
        set_name("藤甲", ({"teng jia","tengjia","jia","armor"}));
        set_level(2);
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
	    set("long", "一件轻便藤甲。\n");
                set("value", 1500);
                set("material", "wood");
                set("armor_prop/armor", 25);
             }
			 setup();
}
