inherit ITEM;
#include <ansi.h>
#include <taskitem.h>
void create()
{
        set_name("玄武玉"NOR, ({"xuanwu jade", "xuanwu" ,"jade"}));
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
