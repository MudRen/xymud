#include <armor.h>
#include <ansi.h>
inherit AMULET;
void create()
{
        set_name(YELBLU"浮世流云"NOR, ({ "amulet","fushenfu" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("no_put",1);
                set("no_zm",1);
                set("no_drop",1);
                set("no_get",1);
                set("value", 0);
                set("unit", "件");
                set("material", "gold");
		set("value", 0);
                set("armor_prop/intelligence", 4);
                set("armor_prop/dodge", 15);
                set("armor_prop/armor", 30);
        	set("long", HIY"这是小雨西游开站两周年纪念品，保佑你平安。\n"NOR);
        }
        setup();
}

