 // baleno.c
//
// This is the basic equip for players just login.

inherit ITEM;
#include <ansi.h>
void init();
int do_read(string arg);

void create()
{
        set_name(HIB"毛"NOR, ({"mao","mao a mao","ji gen mao"}));
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "册");
                set("long", "一本小册子，封面上<<忘情天书>>龙飞凤舞，气势不凡。\n");
                set("material", "paper");
        set("no_put",1);
//        set("no_give",1);
        set("no_drop", 1);                
        set("no_get",1);
        }
}


void init()
{
        add_action("do_read", "read");
        add_action("do_read", "study");
        add_action("do_read", "du");

}
int do_read(string arg)
{
        object me;
        int sen_cost, gain;

        me=this_player();

        message_vision("娱乐一下，大家笑笑，嘿嘿。\n", me);
        return 1;
}
