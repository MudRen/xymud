// whip.c

#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
        set_name(HIR"烈火鞭"NOR, ({"liehuo bian","whip"}));
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",YEL"上古十二神兵之一：烈火鞭\n"NOR);
                set("unit", "条");
                set("no_put",1);
                set("value", 0);
                set("fz_get",1);
                set("no_zm",1);
                set("no_give",1);

        }
        init_whip(140+random(20));
        setup();
}

