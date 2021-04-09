#include <armor.h>

inherit CLOTH;

void create()
{
	set_name("灰色道袍", ({  "dao pao", "pao", "cloth"}) );
	set("level",4);
    set_weight(3000);
    if( clonep() )
       set_default_object(__FILE__);
    else {
        set("unit", "件");
		set("long", "一件普普通通的灰布道袍。\n");
        set("material", "cloth");
        set("armor_prop/armor", 2);
    }
    setup();
}
