#include <armor.h>
#include <ansi.h>

inherit ARMOR;

void create()
{
        set_name(HIG"新手战甲"NOR, ({"jia", "armor"}));
        set_level(1);
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
		set("long", "一件金线织就的宝甲．\n");
                set("material", "steel");
                set("value", 10000);
                set("armor_prop/armor", 60);
				set("no_sell",1);
				set("no_drop","去垃圾堆丢吧，乱扔会污染环境!\n");
				set("no_give","总管发的装备，可不能乱送人哟！\n");
				set("no_get","想拿总管一叶知秋发的装备？做梦吧!\n");
				set("armor_prop/dodge", -5);
        }
        setup();
}


