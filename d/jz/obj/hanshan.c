//Cracked by Roath
// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("汗衫", ({"han shan", "cloth"}));
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("long", "一件很老的汗衫，已经变颜色了。\n");
                set("unit", "件");
                set("value", 200);
                set("armor_prop/armor", 5);
                        set("level",1);

        }
        setup();
}

