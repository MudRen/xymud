inherit ITEM;
#include <ansi.h>
#include <taskitem.h>
void create()
{
        set_name("白虎玉"NOR, ({"baihu jade", "baihu" ,"jade"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一块古怪的玉石。\n");
                set("unit", "块");
               	set("bigtask_name","先知");
               	set("bigtask_id","xian zhi");
        }
}
