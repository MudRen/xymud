#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("渌水罗衣", ({"fancy skirt", "skirt"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
            set("long",
"这是一件看起来非常典雅的长裙，却不知是什么制成．\n");
                set("value", 2200);
                set("material", "cloth");
                set("armor_type", "cloth");
                set("armor_prop/armor", 10);
		set("armor_prop/dodge", 10);
                set("armor_prop/personality", 3);
                set("female_only", 1);
                        set("level",11);
             }
        setup();
}

