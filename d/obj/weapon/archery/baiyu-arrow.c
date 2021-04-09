// zhentian-arrow.c 震天箭

#include <weapon.h>

inherit ARCHERY;

void create()
{
        set_name("白玉箭", ({ "baiyu jian", "arrow", "jian", "baiyu", "baiyu jian", }) );
        if( clonep() )
        set_default_object(__FILE__);
        else 
        {
                set("long","白玉雕琢而成，入手虽轻，却也伤人于无防。\n");
                set("unit", "壶");
                set("base_unit", "枝");
                set("no_sub",1);
                set("no_sell",1);
                set("base_weight", 0);
                set("base_value", 2000);
                set("value", 200000);
        }
        set_amount(999);
        set("num",10000);
        init_archery(120);
        setup();
}

void add_amount(int v)
{
        if( v>=0 )
                return ::add_amount(v);
        else
        {
                add("num",-1);
                if( query("num")<=0 )
                {
                        set("num",10000);
                        return ::add_amount(v);
                }
                else    return;
        }
}
