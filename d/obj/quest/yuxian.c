//Cracked by Roath

// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
inherit ITEM;
#include <task.h>
void create()
{
        set_name("精制鱼线", ({"yu xian", "yuxian"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "这是江州卖鱼竿的丢失的鱼线。\n");
                set("unit", "根");
               set("owner_name","卖鱼竿的");
               set("owner_id","seller");
        }
}
