#include <ansi.h>
inherit ITEM;

void create()
{
                
        set_name("背阴巷副本进入券", ({"beiyin quan","quan"}) );
        set_weight(5);
        set("no_get",1);

       set("is_monitored",1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", GRN"从这个入口可以进入背阴巷公共副本-每小时刷新一次，每三小时重建一次。(enter door)\n"NOR); 
                set("unit", "个");
                set("lore",1);
                set("value", 500);
        }
        setup();
}
void init()
{
        add_action("do_enter","enter");
}

int do_enter(string arg) 
{
	object npc,me = this_player();
        if( !arg || arg!="door")
                return 0;
	me->delete_temp("maze");
	if( MAZE_D->enter_maze(me, "baihuazhen") )
	{
        	me->set_temp("maze/baihuazhen",1);
        	me->set("maze/baihuazhen",time());
	}
        destruct(this_object());
        return 1;
}

