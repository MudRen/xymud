#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG"碧海银瓶"NOR, ({"yin ping", "ping"}));
        set("changed",1);
        set("no_store",1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "海外修士利用海中奇珍炼制的一瓶灵液，喝(drink)了它能补充内力。\n");
                set("value",50000);
                set("num",1000000);
        }
        setup();
}
