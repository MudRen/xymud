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
	//me->set_temp("maze/公共地图","chang_an");
	if( MAZE_D->enter_maze(me, "beiyin") )
	{
        	me->set_temp("maze/beiyin",1);
        	me->set_temp("maze_dir","beiyin");
        	me->set("maze/beiyin",time());
	}
	else	write("副本创建失败。\n");
        destruct(this_object());
        return 1;
/*	 	
	//新手公共副本，3小时一次
	if( time()<me->query("maze/beiyin")+10800 )
	{
		write("你还是先休息休息再来。\n");
		return 1;
	}
	//防止正好刷新
	npc = new("/d/city/npc/libai");
	npc->delete("chat_chance");
	npc->set_temp("maze/公共地图","chang_an");
	MAZE_D->enter_maze(npc,"beiyin");
	if( environment(npc)->query("virtual_room") )
	{
		destruct(npc);
		me->delete_temp("maze");
		me->set_temp("maze/公共地图","chang_an");
		if( MAZE_D->enter_maze(me, "beiyin") )
	        {
        		me->set_temp("maze/beiyin",1);
        		me->set("maze/beiyin",time());
        	}
        	destruct(this_object());
        	return 1;
        }
        else	write("副本刷新中，请等待片刻。\n");
        if( npc )  destruct(npc);	 
        return 1;
*/        
}

